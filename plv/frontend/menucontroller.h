#ifndef PLV_FRONTEND_MENU_CONTROLLER_H
#define PLV_FRONTEND_MENU_CONTROLLER_H
#include <plv/backend/service.h>
#include <memory>
#include "menuview.h"
#include "types.h"

namespace plv::frontend
{
class MenuController
{
public:
    MenuController(std::shared_ptr<MenuView> view, std::shared_ptr<backend::Service> service);

    auto run() -> Awaitable<void>;

private:
    std::shared_ptr<MenuView> view_;
    std::shared_ptr<backend::Service> service_;
};
}  // namespace plv::frontend
#endif  // PLV_FRONTEND_MENU_CONTROLLER_H