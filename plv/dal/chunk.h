#ifndef PLV_DAL_CHUNK_H
#define PLV_DAL_CHUNK_H

#include <plv/types.h>

namespace plv::dal
{
class Chunk
{
public:
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
}  // namespace plv::dal

#endif  // PLV_DAL_CHUNK_H