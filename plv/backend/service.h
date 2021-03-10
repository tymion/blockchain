#ifndef PLV_BACKEND_SERVICE_H
#define PLV_BACKEND_SERVICE_H
#include <plv/datamodel/block.h>
#include <cstdint>
#include <optional>
#include <string_view>
#include <vector>

namespace plv::backend
{
class Service
{
public:
    using BufferView = std::string_view;
    using Id         = uint32_t;
    using Size       = uint32_t;

    virtual auto getBlockById(Id) -> datamodel::Block                                 = 0;
    virtual auto getDataElementFromBlockById(Id, Id) -> BufferView                    = 0;
    virtual auto getBlockchainLength() -> Size                                        = 0;
    virtual auto getBlockchainStorageSize() -> Size                                   = 0;
    virtual auto addDataElementToCache(BufferView) -> void                            = 0;
    virtual auto getDataElementsFromCache() -> std::optional<std::vector<BufferView>> = 0;
    virtual auto generateBlockFromCache() -> datamodel::Block                         = 0;
};
}  // namespace plv::backend
#endif  // PLV_BACKEND_SERVICE_H