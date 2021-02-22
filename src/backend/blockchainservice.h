#ifndef BACKEND_BLOCKCHAIN_SERVICE_H
#define BACKEND_BLOCKCHAIN_SERVICE_H
#include <asio/awaitable.hpp>
#include <memory>
#include <string_view>
#include <vector>
#include "block.h"
#include "blockchainstorage.h"
#include "service.h"

namespace backend
{
class BlockchainService : public Service
{
public:
    using BufferView = std::string_view;
    using Id         = uint32_t;
    using Size       = uint32_t;

    BlockchainService(std::shared_ptr<BlockchainStorage> storage) : storage_(storage) {}

    auto loadBlockchain() -> void override
    {
        metaBlocks_ = storage_->getMetaBlocks();
    }
    auto storeBlockchain() -> asio::awaitable<void>;
    auto addDataElementToCache(BufferView) -> asio::awaitable<void>;
    auto generateBlockFromCache() -> asio::awaitable<void>;
    auto getBlockById(Id) -> asio::awaitable<model::Block>;
    auto getDataElementFromBlockById(Id, Id) -> asio::awaitable<BufferView>;
    auto getBlockchainLength() -> asio::awaitable<Size>;
    auto getBlockchainStorageSize() -> asio::awaitable<Size>;
    auto checkBlockchainIntegrity() -> asio::awaitable<bool>;

private:
    std::shared_ptr<BlockchainStorage> storage_;
    std::vector<model::MetaBlock> metaBlocks_;
};
}  // namespace backend
#endif  // BACKEND_BLOCKCHAIN_SERVICE_H