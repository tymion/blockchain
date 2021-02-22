#ifndef BACKEND_CHUNK_H
#define BACKEND_CHUNK_H

#include <cstdint>
#include <string_view>

namespace backend
{
class Chunk
{
public:
    using Size       = uint32_t;
    using Offset     = uint32_t;
    using BufferView = std::string_view;

    Chunk(BufferView chunk, Offset offset, Size size) : chunk_(chunk), offset_(offset), size_(size) {}

    auto getChunkSize()
    {
        return size_;
    }

    auto getOffset()
    {
        return offset_;
    }

    auto getData()
    {
        return chunk_;
    }

private:
    Offset offset_;
    Size size_;
    BufferView chunk_{};
};
}  // namespace backend

#endif  // BACKEND_CHUNK_H