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
    asio::io_context ioContext_{1};  // NOLINT(misc-non-private-member-variables-in-classes)
    io::ConsoleReadWriter rw_{ioContext_.get_executor()};
};
}  // namespace

// NOLINTNEXTLINE
TEST_F(ConsoleReadWriterTest, WriteHelloWorld)
{
    co_spawn(
        ioContext_,
        // NOLINTNEXTLINE(readability-identifier-naming)
        [&]() -> asio::awaitable<void> {
            auto txt = "Hello World\n"s;
            co_await rw_.write(txt);
        },
        tests::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(ConsoleReadWriterTest, ReadHelloWorld)
{
    co_spawn(
        ioContext_,
        // NOLINTNEXTLINE(readability-identifier-naming)
        [&]() -> asio::awaitable<void> {
            auto txt = co_await rw_.read();
            co_await rw_.write(txt);
        },
        tests::Detached{});
    ioContext_.run();
}