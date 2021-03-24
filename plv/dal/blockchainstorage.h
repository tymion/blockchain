#ifndef PLV_DAL_BLOCKCHAIN_STORAGE_H
#define PLV_DAL_BLOCKCHAIN_STORAGE_H

#include <plv/io/file.h>
#include <plv/serializers/netstring.h>
#include <gsl/gsl_assert>
#include <memory>
#include <vector>
#include "chunkiterator.h"
#include "metablock.h"
#include "storage.h"

namespace plv::dal
{
class BlockchainStorage : public Storage
{
public:
    BlockchainStorage(std::shared_ptr<ChunkIterator> chunkIter, std::shared_ptr<io::File> file)
        : file_(file), chunkIterator_(chunkIter)
    {
    }

    auto indexStorage() -> void override
    {
        using namespace serializers::netstring;
        metaBlocks_.clear();
        auto chunkOpt = chunkIterator_->getNext();
        while (chunkOpt.has_value())
        {
            uint32_t objectIdx = 0;
            do
            {
                auto chunk                     = chunkOpt->getData().substr(objectIdx);
                auto [blockStart, blockLength] = decodeOffsetAndLength(chunk);
                metaBlocks_.emplace_back(chunkOpt->getOffset() + objectIdx + blockStart, blockLength);
                objectIdx += calculateOffsetOfNextObject(blockStart, blockLength);
            } while (objectIdx < chunkOpt->getChunkSize() - 1);
            chunkOpt = chunkIterator_->getNext();
        }
    }

    auto getBlock(Id id) -> Buffer override
    {
        Expects(id < metaBlocks_.size());
        auto metaBlock = metaBlocks_[id];
        Buffer buffer(metaBlock.blockSize, 0);
        file_->read(buffer, metaBlock.blockOffset, metaBlock.blockSize);
        return buffer;
    }

    auto addBlock(BufferView block) -> void override
    {
        using namespace serializers::netstring;
        auto blockSerialized           = encode(block);
        auto [blockStart, blockLength] = decodeOffsetAndLength(blockSerialized);
        metaBlocks_.emplace_back(file_->getSize() + blockStart, blockLength);
        file_->write(blockSerialized);
    }
    /*
        auto getBlock(const datamodel::MetaBlock& metaBlock) -> datamodel::Block
        {
            datamodel::Block block{};
            Buffer buffer(metaBlock.blockSize, 0);
            file_->read(buffer, metaBlock.blockOffset, metaBlock.blockSize);
            auto [hash, consumed] = netstring::decode(buffer);
            std::copy(std::begin(hash), std::end(hash), block.prevBlockHash.data());
            auto remaining = metaBlock.blockSize - consumed;
            while (remaining > 0)
            {
                auto nextData                  = buffer.substr(consumed, remaining);
                auto [dataElement, consumedDE] = netstring::decode(nextData);
                block.dataElements.emplace_back(dataElement);
                remaining -= consumedDE;
                consumed += consumedDE;
            }
            return block;
        }

        auto getBlockPrevHash(const datamodel::MetaBlock& metaBlock) -> datamodel::Block
        {
            datamodel::Block block{};
            Buffer buffer(metaBlock.blockSize, 0);
            file_->read(buffer, metaBlock.blockOffset, metaBlock.blockSize);
            auto [hash, consumed] = netstring::decode(buffer);
            std::copy(std::begin(hash), std::end(hash), block.prevBlockHash.data());
            auto remaining = metaBlock.blockSize - consumed;
            while (remaining > 0)
            {
                auto nextData                  = buffer.substr(consumed, remaining);
                auto [dataElement, consumedDE] = netstring::decode(nextData);
                block.dataElements.emplace_back(dataElement);
                remaining -= consumedDE;
                consumed += consumedDE;
            }
            return block;
        }
    */
    auto getChainLength() -> Size override
    {
        return metaBlocks_.size();
    }

    auto getStorageSize() -> Size override
    {
        return file_->getSize();
    }

    auto isIndexed() -> bool override
    {
        return !(metaBlocks_.size() == 0 && file_->getSize() != 0);
    }

private:
    std::shared_ptr<io::File> file_{};
    std::shared_ptr<ChunkIterator> chunkIterator_{};
    std::vector<dal::MetaBlock> metaBlocks_{};
    bool indexed_{false};
};
}  // namespace plv::dal
#endif  // PLV_DAL_BLOCKCHAIN_STORAGE_H