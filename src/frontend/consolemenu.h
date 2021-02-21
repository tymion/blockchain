#ifndef FRONTEND_CONSOLE_MENU_H
#define FRONTEND_CONSOLE_MENU_H

#include <array>
#include <asio/awaitable.hpp>
#include <memory>
#include "menuview.h"

namespace frontend
{
constexpr auto WELCOME_STR          = "Welcome to Blockchain Service.";
constexpr auto CHOOSE_MSG           = "Please choose action:";
constexpr auto MAINMENU_OPTIONS_CNT = 9;

template <typename ReadWriter>
class ConsoleMenu : public MenuView
{
public:
    ConsoleMenu(std::shared_ptr<ReadWriter> rw) : rw_(rw) {}

    auto displayMainMenu() -> asio::awaitable<void> override
    {
        for (auto i = 0; i < MAINMENU_OPTIONS_CNT; i++)
        {
            co_await rw_->write(mainMenu_[i]);
        }
    }

    auto clearScreen() -> asio::awaitable<void> override
    {
        constexpr auto CLEAR = "\x1B[2J\x1B[H";
        co_await rw_->write(CLEAR);
    }

    auto displayCloseMessage() -> asio::awaitable<void> override
    {
        constexpr auto CLOSE = "Received 'q'. Closing.";
        co_await rw_->write(CLOSE);
    }

    auto displayRequestForBuffer() -> asio::awaitable<void> override
    {
        constexpr auto MSG = "Please provide data element:";
        co_await rw_->write(MSG);
    }

    auto displayRequestForBlockId() -> asio::awaitable<void> override
    {
        constexpr auto MSG = "Please provide block id:";
        co_await rw_->write(MSG);
    }

    auto displayRequestForDataElementId() -> asio::awaitable<void> override
    {
        constexpr auto MSG = "Please provide data element id:";
        co_await rw_->write(MSG);
    }

    auto displayActionDoneMessage() -> asio::awaitable<void> override
    {
        constexpr auto MSG = "Please provide data element id:";
        co_await rw_->write(MSG);
    }

    auto displayBlockMessage() -> asio::awaitable<void> override
    {
        constexpr auto MSG = "Please provide data element id:";
        co_await rw_->write(MSG);
    }

    auto displayStatisticsMessage() -> asio::awaitable<void> override
    {
        constexpr auto MSG = "Please provide data element id:";
        co_await rw_->write(MSG);
    }

    auto getUserEvent() -> asio::awaitable<MenuView::UserEvent> override
    {
        while (auto actionIdx = std::stoi(co_await rw_->read()))
        {
            if (actionIdx > static_cast<int>(MenuView::UserEvent::InvalidEvent) ||
                actionIdx < static_cast<int>(MenuView::UserEvent::Cnt))
            {
                co_return static_cast<MenuView::UserEvent>(actionIdx);
            }
            constexpr auto ERROR = "Invalid input passed. Try again:";
            co_await rw_->write(ERROR);
        }
        co_return MenuView::UserEvent::InvalidEvent;
    }

    auto getBuffer() -> asio::awaitable<Buffer> override
    {
        return rw_->read();
        // co_return std::move(co_await rw_->read());
    }

    auto getId() -> asio::awaitable<Id> override
    {
        co_return 0;
    }

private:
    std::shared_ptr<ReadWriter> rw_;
    std::array<std::string, MAINMENU_OPTIONS_CNT> mainMenu_ = {
        "Read the blockchain from the disk",
        "Write the blockchain to the disk",
        "Accept new daa elements to the buffer",
        "Generate a new block from the buffer",
        "Get the specific block",
        "Get the specific element of a specific block",
        "Get blockchain statistics (number of blocks, total size in bytes)",
        "Check blockchain integrity",
        "Quit"};
};
}  // namespace frontend
#endif  // FRONTEND_CONSOLE_MENU_H