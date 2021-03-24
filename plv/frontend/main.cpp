#include <plv/backend/blockchainservice.h>
#include <plv/crypto/crypto.h>
#include <plv/dal/blockchainstorage.h>
#include <plv/dal/blockparser.h>
#include <plv/dal/chunkiterator.h>
#include <plv/io/consolereadwriter.h>
#include <plv/io/filedescriptor.h>
#include <asio/awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <iostream>
#include <stdexcept>
#include "consolemenuview.h"
#include "menucontroller.h"
#include "menuview.h"

namespace
{
using namespace std::literals;
using namespace plv;
}  // namespace

// NOLINTNEXTLINE
int main(int argc, char* argv[])
{
    try
    {
        // io for backend
        auto filename                  = "storage.bin"sv;
        std::shared_ptr<io::File> file = std::make_shared<io::FileDescriptor>(filename);
        // backend
        std::shared_ptr<dal::ChunkIterator> iterator    = std::make_shared<dal::ChunkIterator>(file);
        std::shared_ptr<dal::BlockchainStorage> storage = std::make_shared<dal::BlockchainStorage>(iterator, file);
        std::shared_ptr<backend::Service> backend =
            std::make_shared<backend::BlockchainService<dal::BlockParser, crypto::Crypto>>(storage);

        // io for frontend
        asio::io_context ioContext{1};
        std::shared_ptr<io::ConsoleReadWriter> rw = std::make_shared<io::ConsoleReadWriter>(ioContext.get_executor());
        // frontend
        std::shared_ptr<frontend::MenuView> menuView =
            std::make_shared<frontend::ConsoleMenuView<io::ConsoleReadWriter>>(rw);

        std::shared_ptr<frontend::MenuController> controller =
            std::make_shared<frontend::MenuController>(menuView, backend);
        asio::co_spawn(
            ioContext,
            // NOLINTNEXTLINE
            [&]() -> asio::awaitable<void> {
                try
                {
                    co_await controller->run();
                }
                catch (const std::exception& ex)
                {
                    std::cout << "Unhandled exception:" << ex.what() << std::endl;
                }
            },
            asio::detached);
        ioContext.run();
    }
    catch (std::exception& ex)
    {
        std::cout << "Last unhandled exception:" << ex.what() << std::endl;
    }
}