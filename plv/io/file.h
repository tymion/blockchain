#ifndef PLV_IO_FILE_H
#define PLV_IO_FILE_H

#include <plv/types.h>

namespace plv::io
{
class File
{
public:
    virtual auto read(Buffer&, Offset, Size) -> void = 0;

    virtual auto read(Buffer&, Size) -> void = 0;

    virtual auto write(BufferView) -> void = 0;

    virtual auto getSize() -> Size = 0;

    virtual auto setPosition(Offset) -> void = 0;

    virtual ~File() = default;
};
}  // namespace plv::io
#endif  // PLV_IO_FILE_H