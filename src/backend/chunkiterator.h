#ifndef BACKEND_CHUNK_ITERATOR_H
#define BACKEND_CHUNK_ITERATOR_H

#include <io/file.h>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include "chunk.h"

namespace backend
{
constexpr uint32_t CHUNK_SIZE = 4 * 1024;
class ChunkIterator
{
public:
    using Size       = uint32_t;
    using Buffer     = std::string;
    using BufferView = std::string_view;

    ChunkIterator(std::shared_ptr<io::File> file) : file_(file), size_(file_->getSize()), leftToRead_(file_->getSize())
    {
        chunk_.reserve(CHUNK_SIZE);
    }

    auto getNext() -> std::optional<Chunk>
    {
        if (leftToRead_ == 0)
        {
            return {};
        }
        auto readLength = CHUNK_SIZE;
        if (readLength > leftToRead_)
        {
            readLength = leftToRead_;
        }
        file_->read(chunk_, readLength);
        auto chunkOffset = size_ - leftToRead_;
        leftToRead_ -= readLength;

        return Chunk{BufferView{chunk_}.substr(0, readLength), chunkOffset, readLength};
    }

private:
    std::shared_ptr<io::File> file_;
    Size leftToRead_{};
    Size size_{};
    Buffer chunk_{};
};
}  // namespace backend

#endif  // BACKEND_CHUNK_ITERATOR_H