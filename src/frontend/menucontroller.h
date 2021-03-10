#ifndef FRONTEND_MENU_CONTROLLER_H
#define FRONTEND_MENU_CONTROLLER_H
#include <backend/service.h>
#include <asio/awaitable.hpp>
#include <memory>
#include "menuview.h"

namespace frontend
{
class MenuController
{
public:
    MenuController(std::shared_ptr<MenuView> view, std::shared_ptr<backend::Service> service);

    auto run() -> asio::awaitable<void>;

private:
    std::shared_ptr<MenuView> view_;
    std::shared_ptr<backend::Service> service_;
};
}  // namespace frontend
#endif  // FRONTEND_MENU_CONTROLLER_H