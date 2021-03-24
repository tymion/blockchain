#ifndef SERIALIZERS_NETSTRING_H
#define SERIALIZERS_NETSTRING_H

#include <fmt/format.h>
#include <algorithm>
#include <charconv>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

namespace plv::serializers::netstring

{
using Size       = uint32_t;
using Offset     = uint32_t;
using Buffer     = std::string;
using BufferView = std::string_view;

auto decodeOffsetAndLength(BufferView buffer) -> std::pair<Size, Size>
{
    using namespace std;
    constexpr auto MIN_MSG_LEN = sizeof("0:,") - 1;
    if (buffer.size() < MIN_MSG_LEN)
    {
        throw std::logic_error("Invalid data. Too short buffer.");
    }
    auto colonIdx   = buffer.find_first_of(":");
    auto dataLength = Size{};
    if (from_chars(begin(buffer), begin(buffer) + colonIdx, dataLength).ec != errc{})
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

inline auto calculate(Offset offset, Size length)
{
    constexpr auto SYNTAX_LEN = sizeof(',');
    return offset + length + SYNTAX_LEN;
}

auto decode(BufferView buffer) -> std::pair<BufferView, Size>
{
    auto [dataIdx, dataLength] = decodeOffsetAndLength(buffer);
    auto commaIdx              = dataIdx + dataLength;
    if (commaIdx >= buffer.length())
    {
        throw std::logic_error("Invalid data. Buffer shorter than expected.");
    }
    if (buffer.at(commaIdx) != ',')
    {
        throw std::logic_error("Invalid data. There should be ','.");
    }
    return {buffer.substr(dataIdx, dataLength), commaIdx + 1};
}

auto encode(BufferView buffer) -> Buffer
{
    return fmt::format("{}:{},", buffer.size(), buffer);
}
}  // namespace plv::serializers::netstring

#endif  // SERIALIZERS_NETSTRING_H