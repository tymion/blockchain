#ifndef PLV_IO_FILE_H
#define PLV_IO_FILE_H

#include <fstream>
#include <string>
#include <string_view>

namespace plv::io
{
class File
{
public:
    using BufferView = std::string_view;
    using Buffer     = std::string;
    using Size       = uint32_t;
    using Offset     = uint32_t;

    virtual auto read(Buffer&, Offset, Size) -> void = 0;

    virtual auto read(Buffer&, Size) -> void = 0;

    virtual auto write(BufferView) -> void = 0;

    virtual auto getSize() -> Size = 0;

    virtual auto setPosition(Offset) -> void = 0;
};
}  // namespace plv::io
#endif  // PLV_IO_FILE_H