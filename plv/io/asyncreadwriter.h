#ifndef PLV_IO_ASYNC_READ_WRITER_H
#define PLV_IO_ASYNC_READ_WRITER_H

#include "types.h"

namespace plv::io
{
class AsyncReadWriter
{
public:
    virtual ~AsyncReadWriter() = default;

    virtual auto write(BufferView buffer) noexcept -> Awaitable<void> = 0;

    virtual auto read() -> Awaitable<Buffer> = 0;
};
}  // namespace plv::io

#endif  // PLV_IO_ASYNC_READ_WRITER_H