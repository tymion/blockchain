#ifndef META_BLOCK_H
#define META_BLOCK_H

#include <cstdint>

namespace model
{
struct MetaBlock
{
    using Offset = uint32_t;
    using Size   = uint32_t;

    MetaBlock(Offset offset, Size size) : blockOffset(offset), blockSize(size) {}

    Offset blockOffset;
    Size blockSize;
};

inline bool operator==(const MetaBlock& lhs, const MetaBlock& rhs)
{
    return lhs.blockSize == rhs.blockSize && lhs.blockOffset == rhs.blockOffset;
}

}  // namespace model

#endif  // META_BLOCK_H