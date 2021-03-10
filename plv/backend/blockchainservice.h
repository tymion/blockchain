#ifndef PLV_BACKEND_BLOCKCHAIN_SERVICE_H
#define PLV_BACKEND_BLOCKCHAIN_SERVICE_H

#include <plv/dal/storage.h>
#include <plv/datamodel/block.h>
#include <memory>
#include "service.h"

namespace plv::backend
{
template <typename Parser, typename Crypto>
class BlockchainService : public Service
{
public:
    using Buffer = std::string;

    BlockchainService(std::shared_ptr<dal::Storage> storage) : storage_(storage) {}

    auto addDataElementToCache(BufferView dataElement) -> void override
    {
        elementsCache_.emplace_back(dataElement);
    }

    auto getDataElementsFromCache() -> std::optional<std::vector<BufferView>> override
    {
        if (elementsCache_.empty())
        {
            return {};
        }
        return std::vector<BufferView>{std::begin(elementsCache_), std::end(elementsCache_)};
    }

    auto generateBlockFromCache() -> datamodel::Block override
    {
        if (elementsCache_.empty())
        {
            throw std::invalid_argument("Todo");
        }
        auto prevBlock = storage_->getBlock(getBlockchainLength() - 1);
        auto block     = datamodel::Block{};
        Crypto::sha256(prevBlock, block.prevBlockHash);
        block.dataElements.reserve(elementsCache_.size());
        std::move(std::begin(elementsCache_), std::end(elementsCache_), std::back_inserter(block.dataElements));
        elementsCache_.erase(std::begin(elementsCache_), std::end(elementsCache_));
        storage_->addBlock(Parser::serialize(block));
        return block;
    }

    auto getBlockById(Id id) -> datamodel::Block override
    {
        if (id < getBlockchainLength())
        {
            return Parser::deserialize(storage_->getBlock(id));
        }
        throw std::invalid_argument("Requested block id is out of blockchain range.");
    }

    auto getDataElementFromBlockById(Id blockId, Id elementId) -> BufferView override
    {
        auto block = getBlockById(blockId);
        if (elementId < block.dataElements.size())
        {
            return block.dataElements[elementId];
        }
        throw std::invalid_argument("Requested data element id is out of range.");
    }

    auto getBlockchainLength() -> Size override
    {
        return storage_->getChainLength();
    }

    auto getBlockchainStorageSize() -> Size override
    {
        return storage_->getStorageSize();
    }

    auto checkBlockchainIntegrity() -> bool
    {
        return false;
    }

private:
    std::vector<Buffer> elementsCache_;
    std::vector<datamodel::Block> blocksCache_;
    std::shared_ptr<dal::Storage> storage_;
};
}  // namespace plv::backend
#endif  // PLV_BACKEND_BLOCKCHAIN_SERVICE_H