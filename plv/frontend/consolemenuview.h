#ifndef PLV_FRONTEND_CONSOLE_MENU_VIEW_H
#define PLV_FRONTEND_CONSOLE_MENU_VIEW_H

#include <fmt/format.h>
#include <array>
#include <memory>
#include <sstream>
#include "menuview.h"

namespace plv::frontend
{
constexpr auto WELCOME_STR          = "Welcome to Blockchain Service.";
constexpr auto CHOOSE_MSG           = "Please choose action:";
constexpr auto MAINMENU_OPTIONS_CNT = static_cast<int>(MenuView::UserEvent::Cnt);

template <typename ReadWriter>
class ConsoleMenuView : public MenuView
{
public:
    ConsoleMenuView(std::shared_ptr<ReadWriter> rw) : rw_(rw) {}

    auto displayMainMenu() -> Awaitable<void> override
    {
        for (auto i = 0; i < UserEvent::Cnt; i++)
        {
            auto msg = fmt::format("{}) {}", i, mainMenu_[i]);
            co_await rw_->write(msg);
        }
    }

    auto clearScreen() -> Awaitable<void> override
    {
        constexpr auto CLEAR = "\x1B[2J\x1B[H";
        co_await rw_->write(CLEAR);
    }

    auto displayCloseMessage() -> Awaitable<void> override
    {
        constexpr auto CLOSE = "Received 'q'. Closing.";
        co_await rw_->write(CLOSE);
    }

    auto displayRequestForBuffer() -> Awaitable<void> override
    {
        constexpr auto MSG = "Please provide data element:\n";
        co_await rw_->write(MSG);
    }

    auto displayRequestForBlockId() -> Awaitable<void> override
    {
        constexpr auto MSG = "Please provide block id:\n";
        co_await rw_->write(MSG);
    }

    auto displayRequestForDataElementId() -> Awaitable<void> override
    {
        constexpr auto MSG = "Please provide data element id:\n";
        co_await rw_->write(MSG);
    }

    auto displayActionDoneMessage() -> Awaitable<void> override
    {
        constexpr auto MSG = "Done. Please press any key to return to main menu.\n";
        co_await rw_->write(MSG);
    }

    auto displayBlockMessage(const datamodel::Block& block) -> Awaitable<void> override
    {
        constexpr auto MSG_FMT = "Requested block:\nPrev block hash:{}\n";
        std::stringstream sstream;
        std::for_each(std::begin(block.prevBlockHash), std::end(block.prevBlockHash),
                      [&](auto& item) { sstream << std::hex << (int)item; });
        auto msg = fmt::format(MSG_FMT, sstream.str());
        for (auto& element : block.dataElements)
        {
            msg += fmt::format("DataElement:{}\n", element);
        }
        co_await rw_->write(msg);
    }

    auto displayDataElementMessage(BufferView element) -> Awaitable<void> override
    {
        auto msg = fmt::format("Requested data element:{}\n", element);
        co_await rw_->write(msg);
    }

    auto displayStatisticsMessage(Size blockchainLength, Size storageSize) -> Awaitable<void> override
    {
        constexpr auto MSG_FMT = "Statistics:\nBlockchain length:{}\nStorage size:{}\n";
        auto msg               = fmt::format(MSG_FMT, blockchainLength, storageSize);
        co_await rw_->write(msg);
    }

    auto displayBlockchainIntegrityMessage(bool integral) -> Awaitable<void> override
    {
        constexpr auto MSG_FMT = "Blockchain integrity:{}\n";
        auto msg               = fmt::format(MSG_FMT, integral ? "True" : "False");
        co_await rw_->write(msg);
    }

    auto displayMessage(BufferView msg) -> Awaitable<void> override
    {
        co_await rw_->write(msg);
        co_await rw_->write("\n");
    }

    auto getUserEvent() -> Awaitable<MenuView::UserEvent> override
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

    auto waitForAnyKey() -> Awaitable<void> override
    {
        co_await rw_->read();
    }

    auto getBuffer() -> Awaitable<Buffer> override
    {
        auto result = co_await rw_->read();
        result.erase(begin(result) + result.size() - 1, end(result));
        co_return result;
        // co_return std::move(co_await rw_->read());
    }

    auto getId() -> Awaitable<Id> override
    {
        auto buffer = co_await rw_->read();
        co_return std::stoi(buffer);
    }

private:
    std::shared_ptr<ReadWriter> rw_;
    std::array<std::string, MAINMENU_OPTIONS_CNT> mainMenu_ = {
        "Read the blockchain from the disk\n",
        "Write the blockchain to the disk\n",
        "Accept new data elements to the buffer\n",
        "Generate a new block from the buffer\n",
        "Get the specific block\n",
        "Get the specific element of a specific block\n",
        "Get blockchain statistics (number of blocks, total size in bytes)\n",
        "Check blockchain integrity\n",
        "Quit\n"};
};  // namespace plv::frontend
}  // namespace plv::frontend
#endif  // PLV_FRONTEND_CONSOLE_MENU_VIEW_H