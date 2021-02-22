#ifndef BACKEND_NETSTRING_H
#define BACKEND_NETSTRING_H

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <stdexcept>
#include <string_view>

namespace backend::netstring
{
using Size       = uint32_t;
using Offset     = uint32_t;
using BufferView = std::string_view;

auto decodeOffsetAndLength(BufferView buffer) -> std::pair<Size, Size>
{
    constexpr auto MIN_MSG_LEN = sizeof("0:,") - 1;
    if (buffer.size() < MIN_MSG_LEN)
    {
        return {{}, {}};
    }
    auto colonIdx   = buffer.find_first_of(":");
    auto dataLength = Size{};
    if (std::from_chars(std::begin(buffer), std::begin(buffer) + colonIdx, dataLength).ec != std::errc{})
    {
        throw std::logic_error("Invalid data. There should be only numbers.");
    }
    return {colonIdx + 1, dataLength};
}

inline auto calculateOffsetOfNextObject(Offset offset, Size length)
{
    constexpr auto SYNTAX_LEN = sizeof(',');
    return offset + length + SYNTAX_LEN;
}

auto decode(BufferView buffer) -> std::pair<BufferView, Size>
{
    auto [colonIdx, dataLength] = decodeOffsetAndLength(buffer);
    auto commaIdx               = colonIdx + dataLength + 1;
    if (commaIdx >= buffer.length())
    {
        return {{}, {}};
    }
    if (buffer.at(commaIdx) != ',')
    {
        throw std::logic_error("Invalid data. There should be ','.");
    }
    return {buffer.substr(colonIdx + 1, dataLength), commaIdx + 1};
}

}  // namespace backend::netstring

#endif  // BACKEND_NETSTRING_H