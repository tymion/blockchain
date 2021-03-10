#ifndef PLV_TESTS_DAL_MOCK_STORAGE_H
#define PLV_TESTS_DAL_MOCK_STORAGE_H

#include <gmock/gmock.h>
#include <plv/dal/storage.h>

namespace plv::tests::dal
{
class MockStorage : public plv::dal::Storage
{
public:
    MOCK_METHOD(Buffer, getBlock, (Id), (override));
    MOCK_METHOD(void, addBlock, (BufferView), (override));
    MOCK_METHOD(Size, getChainLength, (), (override));
    MOCK_METHOD(Size, getStorageSize, (), (override));
};
}  // namespace plv::tests::dal
#endif  // PLV_TESTS_DAL_MOCK_STORAGE_H