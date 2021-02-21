#ifndef IO_MOCK_ASYNC_READ_WRITER_H
#define IO_MOCK_ASYNC_READ_WRITER_H

#include <gmock/gmock.h>
#include <io/asyncreadwriter.h>

namespace io::tests
{
class MockAsyncReadWriter : public AsyncReadWriter
{
public:
    MOCK_METHOD(asio::awaitable<void>, write, (std::string_view), (override));
    MOCK_METHOD(asio::awaitable<std::string>, read, (), (override));
};

}  // namespace io::tests

#endif  // IO_MOCK_ASYNC_READ_WRITER_H
