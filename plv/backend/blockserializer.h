#ifndef BACKEND_BLOCK_SERIALIZER_H
#define BACKEND_BLOCK_SERIALIZER_H

#include <cstdint>
#include <string>
#include <string_view>
#include <utility>

namespace backend
{
class BlockSerializer
{
public:
    using Size       = uint32_t;
    using Buffer     = std::string;
    using BufferView = std::string_view;

    virtual auto deserialize(std::string_view) -> std::pair<Object, Size> = 0;

    virtual auto serialize(const Object&) -> Buffer = 0;
};
}  // namespace backend

#endif  // BACKEND_BLOCK_SERIALIZER_H