#ifndef PLV_IO_MOCK_ASYNC_READ_WRITER_H
#define PLV_IO_MOCK_ASYNC_READ_WRITER_H

#include <gmock/gmock.h>
#include <plv/io/asyncreadwriter.h>

namespace plv::tests::io
{
class MockAsyncReadWriter : public plv::io::AsyncReadWriter
{
public:
    MockAsyncReadWriter()
    {
        ON_CALL(*this, write).WillByDefault([](auto) -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, read).WillByDefault([]() -> asio::awaitable<std::string> { co_return std::string{}; });
    }

    MOCK_METHOD(asio::awaitable<void>, write, (std::string_view), (noexcept, override));
    MOCK_METHOD(asio::awaitable<std::string>, read, (), (override));
};

}  // namespace plv::tests::io

#endif  // PLV_IO_MOCK_ASYNC_READ_WRITER_H
