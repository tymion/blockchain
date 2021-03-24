#ifndef PLV_DAL_META_BLOCK_H
#define PLV_DAL_META_BLOCK_H

#include <plv/types.h>

namespace plv::dal
{
struct MetaBlock
{
    MetaBlock(Offset offset, Size size) : blockOffset(offset), blockSize(size) {}

    Offset blockOffset;
    Size blockSize;
};

inline bool operator==(const MetaBlock& lhs, const MetaBlock& rhs)
{
    return lhs.blockSize == rhs.blockSize && lhs.blockOffset == rhs.blockOffset;
}

}  // namespace plv::dal

#endif  // PLV_DAL_META_BLOCK_H