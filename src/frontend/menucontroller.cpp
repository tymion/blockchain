#include "menucontroller.h"
#include <functional>
#include <stdexcept>
#include <unordered_map>

namespace
{
using namespace frontend;

std::unordered_map<MenuView::UserEvent, std::function<asio::awaitable<void>(std::shared_ptr<MenuView>)>>
    eventToActionMap = {
        {MenuView::UserEvent::ReadBlockchain,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view) -> asio::awaitable<void> { co_await view->displayActionDoneMessage(); }},
        {MenuView::UserEvent::WriteBlockchain,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view) -> asio::awaitable<void> { co_await view->displayActionDoneMessage(); }},
        {MenuView::UserEvent::AddDataElement,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view) -> asio::awaitable<void> {
             co_await view->displayRequestForBuffer();
             auto buffer = co_await view->getBuffer();
             co_await view->displayActionDoneMessage();
         }},
        {MenuView::UserEvent::GenerateBlockchain,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view) -> asio::awaitable<void> { co_await view->displayBlockMessage(); }},
        {MenuView::UserEvent::GetBlock,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view) -> asio::awaitable<void> {
             co_await view->displayRequestForBlockId();
             auto blockId = co_await view->getId();
             co_await view->displayBlockMessage();
         }},
        {MenuView::UserEvent::GetDataElement,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view) -> asio::awaitable<void> {
             co_await view->displayRequestForBlockId();
             auto blockId = co_await view->getId();
             co_await view->displayRequestForDataElementId();
             auto elementId = co_await view->getId();
         }},
        {MenuView::UserEvent::GetStatistics,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view) -> asio::awaitable<void> { co_await view->displayStatisticsMessage(); }},
        {MenuView::UserEvent::CheckIntegrity,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view) -> asio::awaitable<void> { co_return; }},
};
}  // namespace

MenuController::MenuController(std::shared_ptr<MenuView> view) : view_(std::move(view)) {}

// NOLINTNEXTLINE(readability-identifier-naming)
auto MenuController::run() -> asio::awaitable<void>
{
    while (true)
    {
        co_await view_->displayMainMenu();
        auto event = co_await view_->getUserEvent();
        if (event == MenuView::UserEvent::QuitApplication)
        {
            co_return;
        }
        auto action = eventToActionMap.find(event);
        if (action == eventToActionMap.end())
        {
            // it would be better to use asserts from GSL
            throw std::runtime_error("Shouldn't happen.");
        }
        co_await action->second(view_);
    }
}