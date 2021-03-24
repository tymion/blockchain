#ifndef PLV_BACKEND_BLOCKCHAIN_SERVICE_H
#define PLV_BACKEND_BLOCKCHAIN_SERVICE_H

#include <plv/dal/storage.h>
#include <plv/datamodel/block.h>
#include <algorithm>
#include <memory>
#include "service.h"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace plv::backend
{
template <typename Parser, typename Crypto>
class BlockchainService : public Service
{
public:
    BlockchainService(std::shared_ptr<dal::Storage> storage) : storage_(storage) {}

    auto readStorage() -> void override
    {
        storage_->indexStorage();
    }

    auto saveCacheInStorage() -> void override
    {
        using namespace std;
        for_each(begin(blocksCache_), end(blocksCache_),
                 [&](auto& block) { storage_->addBlock(Parser::serialize(block)); });
        blocksCache_.erase(std::begin(blocksCache_), std::end(blocksCache_));
    }

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
            throw std::invalid_argument("Creating empty block is illegal.");
        }
        if (!storage_->isIndexed())
        {
            throw std::invalid_argument("Blockchain storage wasn't indexed. Cannot proceed.");
        }
        auto block = datamodel::Block{};
        block.dataElements.reserve(elementsCache_.size());
        std::move(std::begin(elementsCache_), std::end(elementsCache_), std::back_inserter(block.dataElements));
        elementsCache_.erase(std::begin(elementsCache_), std::end(elementsCache_));
        auto len = getBlockchainLength();
        if (blocksCache_.size() != 0)
        {
            auto prevBlock = Parser::serialize(blocksCache_[blocksCache_.size() - 1]);
            Crypto::sha256(prevBlock, block.prevBlockHash);
        }
        else if (len != 0)
        {
            auto prevBlock = storage_->getBlock(len - 1);
            Crypto::sha256(prevBlock, block.prevBlockHash);
        }
        blocksCache_.push_back(block);
        return block;
    }

    auto getBlockById(Id id) -> datamodel::Block override
    {
        auto len = getBlockchainLength();
        if (id < len)
        {
            return Parser::deserialize(storage_->getBlock(id));
        }
        if (id < len + blocksCache_.size())
        {
            return blocksCache_[id - len];
        }
        throw std::invalid_argument("Requested block id is out of blockchain range.");
    }

    auto getDataElementFromBlockById(Id blockId, Id elementId) -> Buffer override
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

    auto checkBlockchainIntegrity() -> bool override
    {
        if (!storage_->isIndexed())
        {
            throw std::invalid_argument("Blockchain storage wasn't indexed. Cannot proceed.");
        }
        if (storage_->getChainLength() + blocksCache_.size() < 2)
        {
            return true;
        }
        DigestArray prevHash{};
        Buffer prevBlockStr{};
        for (auto i = 0; i < storage_->getChainLength(); i++)
        {
            auto blockStr = storage_->getBlock(i);
            auto block    = Parser::deserialize(blockStr);
            if (prevHash != block.prevBlockHash)
            {
                return false;
            }
            std::fill(std::begin(prevHash), std::end(prevHash), 0);
            Crypto::sha256(blockStr, prevHash);
        }
        for (auto i = 0; i < blocksCache_.size(); i++)
        {
            auto block = blocksCache_[i];
            if (prevHash != block.prevBlockHash)
            {
                return false;
            }
            auto blockStr = Parser::serialize(block);
            std::fill(std::begin(prevHash), std::end(prevHash), 0);
            Crypto::sha256(blockStr, prevHash);
        }

        return true;
    }

private:
    std::vector<Buffer> elementsCache_;
    std::vector<datamodel::Block> blocksCache_;
    std::shared_ptr<dal::Storage> storage_;
};
}  // namespace plv::backend
#endif  // PLV_BACKEND_BLOCKCHAIN_SERVICE_H