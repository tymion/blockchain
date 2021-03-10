#ifndef PLV_FRONTEND_CONSOLE_MENU_H
#define PLV_FRONTEND_CONSOLE_MENU_H

#include <fmt/format.h>
#include <array>
#include <asio/awaitable.hpp>
#include <memory>
#include "menuview.h"

namespace plv::frontend
{
constexpr auto WELCOME_STR          = "Welcome to Blockchain Service.";
constexpr auto CHOOSE_MSG           = "Please choose action:";
constexpr auto MAINMENU_OPTIONS_CNT = static_cast<int>(MenuView::UserEvent::Cnt);

template <typename ReadWriter>
class ConsoleMenu : public MenuView
{
public:
    ConsoleMenu(std::shared_ptr<ReadWriter> rw) : rw_(rw) {}

    auto displayMainMenu() -> asio::awaitable<void> override
    {
        for (auto i = 0; i < UserEvent::Cnt; i++)
        {
            auto msg = fmt::format("{}) {}", i, mainMenu_[i]);
            co_await rw_->write(msg);
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
        constexpr auto MSG = "Please provide data element:\n";
        co_await rw_->write(MSG);
    }

    auto displayRequestForBlockId() -> asio::awaitable<void> override
    {
        constexpr auto MSG = "Please provide block id:\n";
        co_await rw_->write(MSG);
    }

    auto displayRequestForDataElementId() -> asio::awaitable<void> override
    {
        constexpr auto MSG = "Please provide data element id:\n";
        co_await rw_->write(MSG);
    }

    auto displayActionDoneMessage() -> asio::awaitable<void> override
    {
        constexpr auto MSG = "Done. Please press any key to return to main menu.\n";
        co_await rw_->write(MSG);
    }

    auto displayBlockMessage(const datamodel::Block& block) -> asio::awaitable<void> override
    {
        constexpr auto MSG_FMT = "Requested block:\nPrev block hash:{}\n";
        auto msg               = fmt::format(MSG_FMT, block.prevBlockHash.data());
        for (auto& element : block.dataElements)
        {
            msg += fmt::format("DataElement:{}\n", element);
        }
        co_await rw_->write(msg);
    }

    auto displayStatisticsMessage(Size blockchainLength, Size storageSize) -> asio::awaitable<void> override
    {
        constexpr auto MSG_FMT = "Statistics:\nBlockchain length:{}\nStorage size:{}\n";
        auto msg               = fmt::format(MSG_FMT, blockchainLength, storageSize);
        co_await rw_->write(msg);
    }

    auto getUserEvent() -> asio::awaitable<MenuView::UserEvent> override
    {
        do
        {
            auto data = co_await rw_->read();
            if (data.empty() || data[0] == '\n')
            {
                continue;
            }
            auto actionIdx = std::stoi(data);
            if (actionIdx > static_cast<int>(MenuView::UserEvent::InvalidEvent) ||
                actionIdx < static_cast<int>(MenuView::UserEvent::Cnt))
            {
                co_return static_cast<MenuView::UserEvent>(actionIdx);
            }
            constexpr auto ERROR = "Invalid input passed. Try again:\n";
            co_await rw_->write(ERROR);
        } while (true);
        co_return MenuView::UserEvent::InvalidEvent;
    }

    auto waitForAnyKey() -> asio::awaitable<void> override
    {
        co_await rw_->read();
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
        "Write the blockchain to the disk\n",
        "Accept new data elements to the buffer\n",
        "Generate a new block from the buffer\n",
        "Get the specific block\n",
        "Get the specific element of a specific block\n",
        "Get blockchain statistics (number of blocks, total size in bytes)\n",
        "Check blockchain integrity\n",
        "Quit\n"};
};
}  // namespace plv::frontend
#endif  // PLV_FRONTEND_CONSOLE_MENU_H