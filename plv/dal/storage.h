#ifndef PLV_DAL_STORAGE_H
#define PLV_DAL_STORAGE_H
#include <plv/types.h>

namespace plv::dal
{
class Storage
{
public:
    virtual auto indexStorage() -> void = 0;

    virtual auto getBlock(Id id) -> Buffer = 0;

    virtual auto addBlock(BufferView) -> void = 0;

    virtual auto getChainLength() -> Size = 0;

    virtual auto getStorageSize() -> Size = 0;

    virtual auto isIndexed() -> bool = 0;
};
}  // namespace plv::dal
#endif  // PLV_DAL_STORAGE_H