#ifndef PLV_IO_FILE_DESCRIPTOR_H
#define PLV_IO_FILE_DESCRIPTOR_H

#include <filesystem>
#include <fstream>
#include "file.h"

namespace plv::io
{
class FileDescriptor : public File
{
public:
    FileDescriptor(BufferView fileName) : file_(fileName, std::fstream::in | std::fstream::out | std::fstream::app)
    {
        using namespace std::filesystem;
        path filePath{fileName};
        if (exists(filePath))
        {
            size_ = file_size(filePath);
        }
        else
        {
            file_.open(fileName, std::fstream::out);
            file_.close();
            file_.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
        }
    }

    ~FileDescriptor()
    {
        file_.close();
    }

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
    Size size_{0};
};
}  // namespace plv::io
#endif  // PLV_IO_FILE_DESCRIPTOR_H