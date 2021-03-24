#include "consolereadwriter.h"
#include <asio/read_until.hpp>
#include <asio/streambuf.hpp>
#include <asio/use_awaitable.hpp>
#include <asio/write.hpp>
#include <istream>

namespace plv::io
{
ConsoleReadWriter::ConsoleReadWriter(const asio::any_io_executor& executor)
    : istream_(executor, ::dup(STDIN_FILENO)), ostream_(executor, ::dup(STDOUT_FILENO))
{
}
// NOLINTNEXTLINE(readability-identifier-naming)
auto ConsoleReadWriter::write(BufferView buffer) noexcept -> Awaitable<void>
{
    co_await asio::async_write(ostream_, asio::buffer(buffer.data(), buffer.size()), asio::use_awaitable);
}

// NOLINTNEXTLINE(readability-identifier-naming)
auto ConsoleReadWriter::read() -> Awaitable<Buffer>
{
    asio::streambuf streambuffer;
    co_await asio::async_read_until(istream_, streambuffer, '\n', asio::use_awaitable);
    auto buffer = streambuffer.data();
    // co_return std::string{asio::buffers_begin(buffer), asio::buffers_begin(buffer) + buffer.size() - 2};
    co_return std::string{asio::buffers_begin(buffer), asio::buffers_end(buffer)};
}

}  // namespace plv::io