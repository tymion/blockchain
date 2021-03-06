#include "menucontroller.h"
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/this_coro.hpp>
#include <functional>
#include <stdexcept>
#include <unordered_map>

namespace
{
using namespace plv::frontend;
using namespace plv::backend;

std::unordered_map<MenuView::UserEvent,
                   std::function<asio::awaitable<void>(std::shared_ptr<MenuView>, std::shared_ptr<Service>)>>
    eventToActionMap = {
        {MenuView::UserEvent::ReadBlockchain,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view, std::shared_ptr<Service> service) -> asio::awaitable<void> {
             service->readStorage();
             co_await view->displayActionDoneMessage();
         }},
        {MenuView::UserEvent::WriteBlockchain,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view, std::shared_ptr<Service> service) -> asio::awaitable<void> {
             service->saveCacheInStorage();
             co_await view->displayActionDoneMessage();
         }},
        {MenuView::UserEvent::AddDataElement,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view, std::shared_ptr<Service> service) -> asio::awaitable<void> {
             co_await view->displayRequestForBuffer();
             auto buffer = co_await view->getBuffer();
             service->addDataElementToCache(buffer);
             co_await view->displayActionDoneMessage();
         }},
        {MenuView::UserEvent::GenerateBlockchain,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view, std::shared_ptr<Service> service) -> asio::awaitable<void> {
             auto block = service->generateBlockFromCache();
             co_await view->displayBlockMessage(block);
         }},
        {MenuView::UserEvent::GetBlock,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view, std::shared_ptr<Service> service) -> asio::awaitable<void> {
             co_await view->displayRequestForBlockId();
             auto blockId = co_await view->getId();
             auto block   = service->getBlockById(blockId);
             co_await view->displayBlockMessage(block);
             co_await view->displayActionDoneMessage();
         }},
        {MenuView::UserEvent::GetDataElement,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view, std::shared_ptr<Service> service) -> asio::awaitable<void> {
             co_await view->displayRequestForBlockId();
             auto blockId = co_await view->getId();
             co_await view->displayRequestForDataElementId();
             auto elementId   = co_await view->getId();
             auto dataElement = service->getDataElementFromBlockById(blockId, elementId);
             co_await view->displayDataElementMessage(dataElement);
             co_await view->displayActionDoneMessage();
         }},
        {MenuView::UserEvent::GetStatistics,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view, std::shared_ptr<Service> service) -> asio::awaitable<void> {
             auto length = service->getBlockchainLength();
             auto size   = service->getBlockchainStorageSize();
             co_await view->displayStatisticsMessage(length, size);
             co_await view->displayActionDoneMessage();
         }},
        {MenuView::UserEvent::CheckIntegrity,
         // NOLINTNEXTLINE(readability-identifier-naming)
         [](std::shared_ptr<MenuView> view, std::shared_ptr<Service> service) -> asio::awaitable<void> {
             auto integral = service->checkBlockchainIntegrity();
             co_await view->displayBlockchainIntegrityMessage(integral);
             co_await view->displayActionDoneMessage();
             co_return;
         }},
};
}  // namespace

MenuController::MenuController(std::shared_ptr<MenuView> view, std::shared_ptr<Service> service)
    : view_(std::move(view)), service_(std::move(service))
{
}

// NOLINTNEXTLINE(readability-identifier-naming)
auto MenuController::run() -> asio::awaitable<void>
{
    auto executor = co_await asio::this_coro::executor;
    while (true)
    {
        co_await view_->clearScreen();
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
        try
        {
            co_await action->second(view_, service_);
        }
        catch (const std::invalid_argument& err)
        {
            asio::co_spawn(
                executor,
                [&, msg = err.what()]() -> asio::awaitable<void> {
                    co_await view_->displayMessage(msg);
                    co_await view_->displayActionDoneMessage();
                },
                asio::detached);
        }
        co_await view_->waitForAnyKey();
    }
}