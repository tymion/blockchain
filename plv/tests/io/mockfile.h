#ifndef PLV_IO_MOCK_FILE_H
#define PLV_IO_MOCK_FILE_H

#include <gmock/gmock.h>
#include <plv/io/file.h>

namespace plv::tests::io
{
class MockFile : public plv::io::File
{
public:
    MOCK_METHOD(void, read, (Buffer&, Offset, Size), (override));
    MOCK_METHOD(void, read, (Buffer&, Size), (override));
    MOCK_METHOD(void, write, (BufferView), (override));
    MOCK_METHOD(Size, getSize, (), (override));
    MOCK_METHOD(void, setPosition, (Offset), (override));
};
}  // namespace plv::tests::io

#endif  // PLV_IO_MOCK_FILE_H
