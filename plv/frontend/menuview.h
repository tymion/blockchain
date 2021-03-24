#ifndef PLV_FRONTEND_MENU_VIEW_H
#define PLV_FRONTEND_MENU_VIEW_H

#include <plv/datamodel/block.h>
#include "types.h"

namespace plv::frontend
{
class MenuView
{
public:
    enum UserEvent
    {
        InvalidEvent = -1,
        ReadBlockchain,
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

    virtual auto displayMainMenu() -> Awaitable<void> = 0;

    virtual auto clearScreen() -> Awaitable<void> = 0;

    virtual auto displayCloseMessage() -> Awaitable<void> = 0;

    virtual auto displayRequestForBuffer() -> Awaitable<void> = 0;

    virtual auto displayRequestForBlockId() -> Awaitable<void> = 0;

    virtual auto displayRequestForDataElementId() -> Awaitable<void> = 0;

    virtual auto displayActionDoneMessage() -> Awaitable<void> = 0;

    virtual auto displayBlockMessage(const datamodel::Block&) -> Awaitable<void> = 0;

    virtual auto displayDataElementMessage(BufferView) -> Awaitable<void> = 0;

    virtual auto displayStatisticsMessage(Size, Size) -> Awaitable<void> = 0;

    virtual auto displayBlockchainIntegrityMessage(bool) -> Awaitable<void> = 0;

    virtual auto displayMessage(BufferView) -> Awaitable<void> = 0;

    virtual auto waitForAnyKey() -> Awaitable<void> = 0;

    virtual auto getUserEvent() -> Awaitable<MenuView::UserEvent> = 0;

    virtual auto getBuffer() -> Awaitable<Buffer> = 0;

    virtual auto getId() -> Awaitable<Id> = 0;
};
}  // namespace plv::frontend
#endif  // PLV_FRONTEND_MENU_VIEW_H