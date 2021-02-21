#ifndef IO_CONSOLE_READ_WRITER_H
#define IO_CONSOLE_READ_WRITER_H

#include <asio/awaitable.hpp>
#include <asio/executor.hpp>
#include <asio/posix/stream_descriptor.hpp>
#include <string>
#include <string_view>
#include "asyncreadwriter.h"

namespace io
{
class ConsoleReadWriter : public AsyncReadWriter
{
public:
    ConsoleReadWriter(const asio::any_io_executor& executor);

    auto write(std::string_view buffer) -> asio::awaitable<void> override;

    auto read() -> asio::awaitable<std::string> override;

private:
    asio::posix::stream_descriptor istream_;
    asio::posix::stream_descriptor ostream_;
};
}  // namespace io

#endif  // IO_CONSOLE_READ_WRITER_H