#include <detached.h>
#include <frontend/consolemenu.h>
#include <gtest/gtest.h>
#include <io/mockasyncreadwriter.h>
#include <asio/co_spawn.hpp>
#include <asio/io_context.hpp>
#include <memory>

namespace
{
using namespace ::testing;
using namespace std::literals;
using namespace io::tests;

constexpr auto MENU_COUNT = static_cast<int>(frontend::MenuView::UserEvent::Cnt);

class ConsoleMenuTest : public Test
{
public:
    asio::io_context ioContext_{1};
    std::shared_ptr<StrictMock<MockAsyncReadWriter>> rw_{std::make_shared<StrictMock<MockAsyncReadWriter>>()};
    std::unique_ptr<frontend::ConsoleMenu<StrictMock<MockAsyncReadWriter>>> menu_{
        std::make_unique<frontend::ConsoleMenu<StrictMock<MockAsyncReadWriter>>>(rw_)};
};
}  // namespace

// NOLINTNEXTLINE
TEST_F(ConsoleMenuTest, displayMainMenu)
{
    EXPECT_CALL(*rw_, write).Times(MENU_COUNT);
    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menu_->displayMainMenu(); }, tests::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(ConsoleMenuTest, clearScreen)
{
    EXPECT_CALL(*rw_, write).Times(1);
    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menu_->clearScreen(); }, tests::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(ConsoleMenuTest, displayCloseMessage)
{
    EXPECT_CALL(*rw_, write).Times(1);
    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menu_->displayCloseMessage(); }, tests::Detached{});
    ioContext_.run();
}