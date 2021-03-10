#ifndef PLV_TESTS_IO_MOCK_MENU_VIEW_H
#define PLV_TESTS_IO_MOCK_MENU_VIEW_H

#include <gmock/gmock.h>
#include <plv/frontend/menuview.h>

namespace plv::tests::frontend
{
class MockMenuView : public plv::frontend::MenuView
{
public:
    MockMenuView()
    {
        ON_CALL(*this, displayMainMenu).WillByDefault([]() -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, clearScreen).WillByDefault([]() -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, displayCloseMessage).WillByDefault([]() -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, displayRequestForBuffer).WillByDefault([]() -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, displayRequestForBlockId).WillByDefault([]() -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, displayRequestForDataElementId).WillByDefault([]() -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, displayActionDoneMessage).WillByDefault([]() -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, displayBlockMessage).WillByDefault([](const auto&) -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, displayStatisticsMessage).WillByDefault([](auto, auto) -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, waitForAnyKey).WillByDefault([]() -> asio::awaitable<void> { co_return; });
        ON_CALL(*this, getUserEvent).WillByDefault([]() -> asio::awaitable<MenuView::UserEvent> {
            co_return MenuView::InvalidEvent;
        });
        ON_CALL(*this, getBuffer).WillByDefault([]() -> asio::awaitable<Buffer> { co_return Buffer{}; });
        ON_CALL(*this, getId).WillByDefault([]() -> asio::awaitable<Id> { co_return Id{}; });
    }

    MOCK_METHOD(asio::awaitable<void>, displayMainMenu, (), (override));
    MOCK_METHOD(asio::awaitable<void>, clearScreen, (), (override));
    MOCK_METHOD(asio::awaitable<void>, displayCloseMessage, (), (override));
    MOCK_METHOD(asio::awaitable<void>, displayRequestForBuffer, (), (override));
    MOCK_METHOD(asio::awaitable<void>, displayRequestForBlockId, (), (override));
    MOCK_METHOD(asio::awaitable<void>, displayRequestForDataElementId, (), (override));
    MOCK_METHOD(asio::awaitable<void>, displayActionDoneMessage, (), (override));
    MOCK_METHOD(asio::awaitable<void>, displayBlockMessage, (const datamodel::Block&), (override));
    MOCK_METHOD(asio::awaitable<void>, displayStatisticsMessage, (Size, Size), (override));
    MOCK_METHOD(asio::awaitable<void>, waitForAnyKey, (), (override));
    MOCK_METHOD(asio::awaitable<MenuView::UserEvent>, getUserEvent, (), (override));
    MOCK_METHOD(asio::awaitable<Buffer>, getBuffer, (), (override));
    MOCK_METHOD(asio::awaitable<Id>, getId, (), (override));
};
}  // namespace plv::tests::frontend

#endif  // PLV_TESTS_IO_MOCK_MENU_VIEW_H
