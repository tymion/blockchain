#ifndef IO_ASYNC_READ_WRITER_H
#define IO_ASYNC_READ_WRITER_H

#include <asio/awaitable.hpp>
#include <string>
#include <string_view>

namespace io
{
class AsyncReadWriter
{
public:
    virtual ~AsyncReadWriter() = default;

    virtual auto write(std::string_view buffer) -> asio::awaitable<void> = 0;

    virtual auto read() -> asio::awaitable<std::string> = 0;
};
}  // namespace io

#endif  // IO_ASYNC_READ_WRITER_H