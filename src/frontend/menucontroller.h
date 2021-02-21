#ifndef FRONTEND_MENU_CONTROLLER_H
#define FRONTEND_MENU_CONTROLLER_H
#include <asio/awaitable.hpp>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include "menuview.h"

namespace frontend
{
class MenuController
{
public:
    MenuController(std::shared_ptr<MenuView> view) : view_(view) {}

    auto run() -> asio::awaitable<void>
    {
        while (true)
        {
            co_await view_->displayMainMenu();
            auto event = co_await view_->getUserEvent();
            if (event == MenuView::UserEvent::QuitApplication)
            {
                co_return;
            }
            auto action = eventToActionMap_.find(event);
            if (action == eventToActionMap_.end())
            {
                // it would be better to use asserts from GSL
                throw std::runtime_error("Shouldn't happen.");
            }
            co_await action->second();
        }
    }

private:
    std::unordered_map<MenuView::UserEvent, std::function<asio::awaitable<void>()>> eventToActionMap_ = {
        {MenuView::UserEvent::ReadBlockchain,
         [&]() -> asio::awaitable<void> { co_await view_->displayActionDoneMessage(); }},
        {MenuView::UserEvent::WriteBlockchain,
         [&]() -> asio::awaitable<void> { co_await view_->displayActionDoneMessage(); }},
        {MenuView::UserEvent::AddDataElement,
         [&]() -> asio::awaitable<void> {
             co_await view_->displayRequestForBuffer();
             auto buffer = co_await view_->getBuffer();
             co_await view_->displayActionDoneMessage();
         }},
        {MenuView::UserEvent::GenerateBlockchain,
         [&]() -> asio::awaitable<void> { co_await view_->displayBlockMessage(); }},
        {MenuView::UserEvent::GetBlock,
         [&]() -> asio::awaitable<void> {
             co_await view_->displayRequestForBlockId();
             auto blockId = co_await view_->getId();
             co_await view_->displayBlockMessage();
         }},
        {MenuView::UserEvent::GetDataElement,
         [&]() -> asio::awaitable<void> {
             co_await view_->displayRequestForBlockId();
             auto blockId = co_await view_->getId();
             co_await view_->displayRequestForDataElementId();
             auto elementId = co_await view_->getId();
         }},
        {MenuView::UserEvent::GetStatistics,
         [&]() -> asio::awaitable<void> { co_await view_->displayStatisticsMessage(); }},
        {MenuView::UserEvent::CheckIntegrity, []() -> asio::awaitable<void> { co_return; }},
    };
    std::shared_ptr<MenuView> view_;
};
}  // namespace frontend
#endif  // FRONTEND_MENU_CONTROLLER_H