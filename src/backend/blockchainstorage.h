#ifndef BACKEND_BLOCKCHAIN_STORAGE_H
#define BACKEND_BLOCKCHAIN_STORAGE_H

#include <io/file.h>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include "chunkiterator.h"
#include "metablock.h"
#include "netstring.h"

namespace backend
{
class BlockchainStorage
{
public:
    using BufferView = std::string_view;

    BlockchainStorage(std::shared_ptr<ChunkIterator> chunkIter, std::shared_ptr<io::File> file)
        : file_(file), chunkIterator_(chunkIter)
    {
    }

    auto getMetaBlocks() -> std::vector<model::MetaBlock>
    {
        std::vector<model::MetaBlock> metaBlockchain{};
        for (auto chunkOpt = chunkIterator_->getNext(); chunkOpt.has_value(); chunkOpt = chunkIterator_->getNext())
        {
            auto consumed = 0;
            do
            {
                auto chunk                     = chunkOpt->getData().substr(consumed);
                auto [blockStart, blockLength] = netstring::decodeOffsetAndLength(chunk);
                metaBlockchain.emplace_back(chunkOpt->getOffset() + consumed + blockStart, blockLength);
                consumed += netstring::calculateOffsetOfNextObject(blockStart, blockLength);
            } while (consumed < chunkOpt->getChunkSize());
        }
        return metaBlockchain;
    }

private:
    std::shared_ptr<io::File> file_;
    std::shared_ptr<ChunkIterator> chunkIterator_;
};
}  // namespace backend
#endif  // BACKEND_BLOCKCHAIN_STORAGE_H