#ifndef PLV_IO_CONSOLE_READ_WRITER_H
#define PLV_IO_CONSOLE_READ_WRITER_H

#include <asio/awaitable.hpp>
#include <asio/executor.hpp>
#include <asio/posix/stream_descriptor.hpp>
#include <string>
#include <string_view>
#include "asyncreadwriter.h"

namespace plv::io
{
class ConsoleReadWriter : public AsyncReadWriter
{
public:
    ConsoleReadWriter(const asio::any_io_executor& executor);

    auto write(BufferView buffer) noexcept -> Awaitable<void> override;

    auto read() -> Awaitable<Buffer> override;

private:
    asio::posix::stream_descriptor istream_;
    asio::posix::stream_descriptor ostream_;
};
}  // namespace plv::io

#endif  // PLV_IO_CONSOLE_READ_WRITER_H