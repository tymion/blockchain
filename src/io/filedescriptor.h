#ifndef IO_FILE_DESCRIPTOR_H
#define IO_FILE_DESCRIPTOR_H

#include <fstream>
#include "file.h"

namespace io
{
class FileDescriptor : public File
{
public:
    FileDescriptor(BufferView fileName) : file_(fileName, std::fstream::in | std::fstream::out), size_(file_.tellg()) {}

    auto read(Buffer& buffer, Offset offset, Size length) -> void override
    {
        setPosition(offset);
        file_.read(&buffer[0], length);
    }

    auto read(Buffer& buffer, Size length) -> void override
    {
        file_.read(&buffer[0], length);
    }

    auto write(BufferView buffer) -> void override
    {
        file_.write(buffer.data(), buffer.size());
        size_ += buffer.size();
    }

    auto getSize() -> Size override
    {
        return size_;
    }

    auto setPosition(Offset offset) -> void override
    {
        file_.seekg(offset);
    }

private:
    std::fstream file_{};
    Size size_{};
};
}  // namespace io
#endif  // IO_FILE_DESCRIPTOR_H