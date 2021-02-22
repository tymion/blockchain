#include <backend/blockchainservice.h>
#include <backend/blockchainstorage.h>
#include <backend/chunkiterator.h>
#include <io/consolereadwriter.h>
#include <io/filedescriptor.h>
#include <asio/awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <iostream>
#include <stdexcept>
#include "consolemenu.h"
#include "menucontroller.h"
#include "menuview.h"

namespace
{
using namespace std::literals;
}

// NOLINTNEXTLINE
int main(int argc, char* argv[])
{
    // io for backend
    auto filename                  = "storage.bin"sv;
    std::shared_ptr<io::File> file = std::make_shared<io::FileDescriptor>(filename);
    // backend
    std::shared_ptr<backend::ChunkIterator> iterator    = std::make_shared<backend::ChunkIterator>(file);
    std::shared_ptr<backend::BlockchainStorage> storage = std::make_shared<backend::BlockchainStorage>(iterator, file);
    std::shared_ptr<backend::Service> backend           = std::make_shared<backend::BlockchainService>(storage);

    // io for frontend
    asio::io_context ioContext{1};
    std::shared_ptr<io::ConsoleReadWriter> rw = std::make_shared<io::ConsoleReadWriter>(ioContext.get_executor());
    // frontend
    std::shared_ptr<frontend::MenuView> menuView = std::make_shared<frontend::ConsoleMenu<io::ConsoleReadWriter>>(rw);

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