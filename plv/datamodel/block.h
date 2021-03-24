#ifndef PLV_DATAMODEL_BLOCK_H
#define PLV_DATAMODEL_BLOCK_H

#include <plv/types.h>

namespace plv::datamodel
{
struct Block
{
    DigestArray prevBlockHash{};
    // PAYLOAD
    BufferSet dataElements{};
};

inline bool operator==(const Block& lhs, const Block& rhs)
{
    return lhs.prevBlockHash == rhs.prevBlockHash && lhs.dataElements == rhs.dataElements;
}

}  // namespace plv::datamodel

#endif  // PLV_DATAMODEL_BLOCK_H