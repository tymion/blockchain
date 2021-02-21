#include <detached.h>
#include <gtest/gtest.h>
#include <io/consolereadwriter.h>
#include <asio/co_spawn.hpp>
#include <asio/io_context.hpp>
#include <memory>

namespace
{
using namespace ::testing;
using namespace std::literals;
using namespace io;

class ConsoleReadWriterTest : public Test
{
public:
    asio::io_context ioContext_{1};
};
}  // namespace

// NOLINTNEXTLINE
TEST_F(ConsoleReadWriterTest, WriteHelloWorld)
{
    co_spawn(
        ioContext_,
        []() -> asio::awaitable<void> {
            auto executor = co_await asio::this_coro::executor;
            auto rw       = std::make_unique<io::ConsoleReadWriter>(executor);
            auto txt      = "Hello World\n"s;
            co_await rw->write(txt);
        },
        tests::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(ConsoleReadWriterTest, ReadHelloWorld)
{
    co_spawn(
        ioContext_,
        []() -> asio::awaitable<void> {
            auto executor = co_await asio::this_coro::executor;
            auto rw       = std::make_unique<io::ConsoleReadWriter>(executor);
            auto txt      = co_await rw->read();
            co_await rw->write(txt);
        },
        tests::Detached{});
    ioContext_.run();
}