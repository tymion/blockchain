#ifndef PLV_IO_ASYNC_READ_WRITER_H
#define PLV_IO_ASYNC_READ_WRITER_H

#include <asio/awaitable.hpp>
#include <string>
#include <string_view>

namespace plv::io
{
class AsyncReadWriter
{
public:
    virtual ~AsyncReadWriter() = default;

    virtual auto write(std::string_view buffer) noexcept -> asio::awaitable<void> = 0;

    virtual auto read() -> asio::awaitable<std::string> = 0;
};
}  // namespace plv::io

#endif  // PLV_IO_ASYNC_READ_WRITER_H