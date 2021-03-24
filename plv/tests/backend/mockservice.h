#ifndef PLV_TESTS_BACKEND_MOCK_SERVICE_H
#define PLV_TESTS_BACKEND_MOCK_SERVICE_H

#include <gmock/gmock.h>
#include <plv/backend/service.h>

namespace plv::tests::backend
{
class MockService : public plv::backend::Service
{
public:
    MOCK_METHOD(datamodel::Block, getBlockById, (Id), (override));
    MOCK_METHOD(Buffer, getDataElementFromBlockById, (Id, Id), (override));
    MOCK_METHOD(Size, getBlockchainLength, (), (override));
    MOCK_METHOD(Size, getBlockchainStorageSize, (), (override));
    MOCK_METHOD(void, saveCacheInStorage, (), (override));
    MOCK_METHOD(void, readStorage, (), (override));
    MOCK_METHOD(void, addDataElementToCache, (BufferView), (override));
    MOCK_METHOD((std::optional<std::vector<BufferView>>), getDataElementsFromCache, (), (override));
    MOCK_METHOD(datamodel::Block, generateBlockFromCache, (), (override));
    MOCK_METHOD(bool, checkBlockchainIntegrity, (), (override));
};
}  // namespace plv::tests::backend

#endif  // PLV_TESTS_BACKEND_MOCK_SERVICE_H
