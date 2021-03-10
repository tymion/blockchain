#include <gtest/gtest.h>
#include <plv/frontend/menucontroller.h>
#include <plv/tests/backend/mockservice.h>
#include <plv/tests/frontend/mockmenuview.h>
#include <plv/tests/utils/detached.h>
#include <asio/co_spawn.hpp>
#include <asio/io_context.hpp>
#include <memory>

namespace
{
using namespace ::testing;
using namespace std::literals;
using namespace plv;
using MenuUserEvent = frontend::MenuView::UserEvent;

class MenuControllerTest : public Test
{
public:
    asio::io_context ioContext_{1};
    Sequence seq_;
    std::shared_ptr<StrictMock<tests::frontend::MockMenuView>> view_{
        std::make_shared<StrictMock<tests::frontend::MockMenuView>>()};
    std::shared_ptr<StrictMock<tests::backend::MockService>> service_{
        std::make_shared<StrictMock<tests::backend::MockService>>()};
    std::unique_ptr<frontend::MenuController> menuController_{
        std::make_unique<frontend::MenuController>(view_, service_)};
};
}  // namespace

// NOLINTNEXTLINE
TEST_F(MenuControllerTest, runWithWriteBlockchain)
{
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::WriteBlockchain;
    });
    EXPECT_CALL(*view_, displayActionDoneMessage).InSequence(seq_);
    EXPECT_CALL(*view_, waitForAnyKey).InSequence(seq_);
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::QuitApplication;
    });

    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menuController_->run(); }, tests::utils::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(MenuControllerTest, runWithAddDataElement)
{
    using namespace std::literals;
    using Buffer    = frontend::MenuView::Buffer;
    auto testBuffer = "BlockchainDataElement"s;
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::AddDataElement;
    });
    EXPECT_CALL(*view_, displayRequestForBuffer).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getBuffer).InSequence(seq_).WillOnce([=]() -> asio::awaitable<Buffer> {
        co_return testBuffer;
    });
    EXPECT_CALL(*view_, displayActionDoneMessage).InSequence(seq_);
    EXPECT_CALL(*view_, waitForAnyKey).InSequence(seq_);
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::QuitApplication;
    });

    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menuController_->run(); }, tests::utils::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(MenuControllerTest, runWithGenerateBlockchain)
{
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::GenerateBlockchain;
    });
    EXPECT_CALL(*service_, generateBlockFromCache).InSequence(seq_);
    EXPECT_CALL(*view_, displayBlockMessage).InSequence(seq_);
    EXPECT_CALL(*view_, waitForAnyKey).InSequence(seq_);
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::QuitApplication;
    });

    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menuController_->run(); }, tests::utils::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(MenuControllerTest, runWithGetBlock)
{
    constexpr auto TEST_ID = 13;
    using Id               = frontend::MenuView::Id;
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::GetBlock;
    });
    EXPECT_CALL(*view_, displayRequestForBlockId).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getId).InSequence(seq_).WillOnce([&]() -> asio::awaitable<Id> { co_return TEST_ID; });
    EXPECT_CALL(*service_, getBlockById).InSequence(seq_);
    EXPECT_CALL(*view_, displayBlockMessage).InSequence(seq_);
    EXPECT_CALL(*view_, displayActionDoneMessage).InSequence(seq_);
    EXPECT_CALL(*view_, waitForAnyKey).InSequence(seq_);
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::QuitApplication;
    });
    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menuController_->run(); }, tests::utils::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(MenuControllerTest, runWithGetDataElement)
{
    constexpr auto TEST_BLOCKID       = 13;
    constexpr auto TEST_DATAELEMENTID = 2;
    using Id                          = frontend::MenuView::Id;
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::GetDataElement;
    });
    EXPECT_CALL(*view_, displayRequestForBlockId).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getId).InSequence(seq_).WillOnce([&]() -> asio::awaitable<Id> { co_return TEST_BLOCKID; });
    EXPECT_CALL(*view_, displayRequestForDataElementId).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getId).InSequence(seq_).WillOnce([&]() -> asio::awaitable<Id> {
        co_return TEST_DATAELEMENTID;
    });
    EXPECT_CALL(*service_, getDataElementFromBlockById).InSequence(seq_);
    EXPECT_CALL(*view_, displayActionDoneMessage).InSequence(seq_);
    EXPECT_CALL(*view_, waitForAnyKey).InSequence(seq_);
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::QuitApplication;
    });

    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menuController_->run(); }, tests::utils::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(MenuControllerTest, runWithGetStatistics)
{
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::GetStatistics;
    });
    EXPECT_CALL(*service_, getBlockchainLength).InSequence(seq_);
    EXPECT_CALL(*service_, getBlockchainStorageSize).InSequence(seq_);
    EXPECT_CALL(*view_, displayStatisticsMessage).InSequence(seq_);
    EXPECT_CALL(*view_, displayActionDoneMessage).InSequence(seq_);
    EXPECT_CALL(*view_, waitForAnyKey).InSequence(seq_);
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::QuitApplication;
    });

    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menuController_->run(); }, tests::utils::Detached{});
    ioContext_.run();
}

// NOLINTNEXTLINE
TEST_F(MenuControllerTest, runWithCheckIntegrity)
{
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::CheckIntegrity;
    });
    EXPECT_CALL(*view_, waitForAnyKey).InSequence(seq_);
    EXPECT_CALL(*view_, clearScreen).InSequence(seq_);
    EXPECT_CALL(*view_, displayMainMenu).InSequence(seq_);
    // NOLINTNEXTLINE(readability-identifier-naming)
    EXPECT_CALL(*view_, getUserEvent).InSequence(seq_).WillOnce([]() -> asio::awaitable<MenuUserEvent> {
        co_return MenuUserEvent::QuitApplication;
    });

    co_spawn(
        // NOLINTNEXTLINE(readability-identifier-naming)
        ioContext_, [&]() -> asio::awaitable<void> { co_await menuController_->run(); }, tests::utils::Detached{});
    ioContext_.run();
}