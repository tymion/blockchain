#ifndef PLV_DAL_STORAGE_H
#define PLV_DAL_STORAGE_H
#include <cstdint>
#include <string>

namespace plv::dal
{
class Storage
{
public:
    using BufferView = std::string_view;
    using Buffer     = std::string;
    using Size       = uint32_t;
    using Id         = uint32_t;

    virtual auto getBlock(Id id) -> Buffer = 0;

    virtual auto addBlock(BufferView) -> void = 0;

    virtual auto getChainLength() -> Size = 0;

    virtual auto getStorageSize() -> Size = 0;
};
}  // namespace plv::dal
#endif  // PLV_DAL_STORAGE_H