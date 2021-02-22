#ifndef IO_MOCK_FILE_H
#define IO_MOCK_FILE_H

#include <gmock/gmock.h>
#include <io/file.h>

namespace io::tests
{
class MockFile : public File
{
public:
    MOCK_METHOD(void, read, (Buffer&, Offset, Size), (override));
    MOCK_METHOD(void, read, (Buffer&, Size), (override));
    MOCK_METHOD(void, write, (BufferView), (override));
    MOCK_METHOD(Size, getSize, (), (override));
    MOCK_METHOD(void, setPosition, (Offset), (override));
};
}  // namespace io::tests

#endif  // IO_MOCK_FILE_H
