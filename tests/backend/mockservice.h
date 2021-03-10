#ifndef BACKEND_MOCK_SERVICE_H
#define BACKEND_MOCK_SERVICE_H

#include <backend/service.h>
#include <gmock/gmock.h>

namespace backend::tests
{
class MockService : public Service
{
public:
    MOCK_METHOD(void, loadBlockchain, (), (override));
};
}  // namespace backend::tests

#endif  // BACKEND_MOCK_SERVICE_H
