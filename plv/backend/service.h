#ifndef PLV_BACKEND_SERVICE_H
#define PLV_BACKEND_SERVICE_H
#include <plv/datamodel/block.h>
#include <plv/types.h>

namespace plv::backend
{
class Service
{
public:
    virtual auto getBlockById(Id id) -> datamodel::Block               = 0;
    virtual auto getDataElementFromBlockById(Id, Id) -> Buffer         = 0;
    virtual auto getBlockchainLength() -> Size                         = 0;
    virtual auto getBlockchainStorageSize() -> Size                    = 0;
    virtual auto saveCacheInStorage() -> void                          = 0;
    virtual auto readStorage() -> void                                 = 0;
    virtual auto addDataElementToCache(BufferView) -> void             = 0;
    virtual auto getDataElementsFromCache() -> Optional<BufferViewSet> = 0;
    virtual auto generateBlockFromCache() -> datamodel::Block          = 0;
    virtual auto checkBlockchainIntegrity() -> bool                    = 0;
};
}  // namespace plv::backend
#endif  // PLV_BACKEND_SERVICE_H