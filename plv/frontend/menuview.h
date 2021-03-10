#ifndef PLV_FRONTEND_MENU_VIEW_H
#define PLV_FRONTEND_MENU_VIEW_H

#include <plv/datamodel/block.h>
#include <asio/awaitable.hpp>

namespace plv::frontend
{
class MenuView
{
public:
    using Buffer = std::string;
    using Id     = uint32_t;
    using Size   = uint32_t;

    enum UserEvent
    {
        InvalidEvent = -1,
        WriteBlockchain,
        AddDataElement,
        GenerateBlockchain,
        GetBlock,
        GetDataElement,
        GetStatistics,
        CheckIntegrity,
        QuitApplication,
        Cnt
    };

    virtual auto displayMainMenu() -> asio::awaitable<void> = 0;

    virtual auto clearScreen() -> asio::awaitable<void> = 0;

    virtual auto displayCloseMessage() -> asio::awaitable<void> = 0;

    virtual auto displayRequestForBuffer() -> asio::awaitable<void> = 0;

    virtual auto displayRequestForBlockId() -> asio::awaitable<void> = 0;

    virtual auto displayRequestForDataElementId() -> asio::awaitable<void> = 0;

    virtual auto displayActionDoneMessage() -> asio::awaitable<void> = 0;

    virtual auto displayBlockMessage(const datamodel::Block&) -> asio::awaitable<void> = 0;

    virtual auto displayStatisticsMessage(Size, Size) -> asio::awaitable<void> = 0;

    virtual auto waitForAnyKey() -> asio::awaitable<void> = 0;

    virtual auto getUserEvent() -> asio::awaitable<MenuView::UserEvent> = 0;

    virtual auto getBuffer() -> asio::awaitable<Buffer> = 0;

    virtual auto getId() -> asio::awaitable<Id> = 0;
};
}  // namespace plv::frontend
#endif  // PLV_FRONTEND_MENU_VIEW_H