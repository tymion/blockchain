#ifndef PLV_DAL_CHUNK_ITERATOR_H
#define PLV_DAL_CHUNK_ITERATOR_H

#include <plv/io/file.h>
#include <plv/types.h>
#include <memory>
#include <optional>
#include "chunk.h"

namespace plv::dal
{
constexpr uint32_t CHUNK_SIZE = 4 * 1024;
class ChunkIterator
{
public:
    ChunkIterator(std::shared_ptr<io::File> file) : file_(file)
    {
        chunk_.resize(CHUNK_SIZE);
    }

    auto getNext() -> std::optional<Chunk>
    {
        if (begin_)
        {
            leftToRead_ = file_->getSize();
            begin_      = false;
        }
        if (leftToRead_ == 0)
        {
            begin_ = true;
            return {};
        }
        auto readLength = CHUNK_SIZE;
        if (readLength > leftToRead_)
        {
            readLength = leftToRead_;
        }
        auto chunkOffset = file_->getSize() - leftToRead_;
        file_->read(chunk_, chunkOffset, readLength);
        leftToRead_ -= readLength;
        auto chunkView = BufferView{chunk_};
        return Chunk{chunkView.substr(0, readLength), chunkOffset, readLength};
    }

private:
    std::shared_ptr<io::File> file_;
    Size leftToRead_{};
    Buffer chunk_{};
    bool begin_{true};
};
}  // namespace plv::dal

#endif  // PLV_DAL_CHUNK_ITERATOR_H