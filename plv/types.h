#ifndef PLV_TYPES_H
#define PLV_TYPES_H
#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace plv
{
constexpr auto SHA256_DIGEST_LEN = 32;

template <typename T>
using Optional      = std::optional<T>;
using BufferView    = std::string_view;
using BufferViewSet = std::vector<std::string_view>;
using Buffer        = std::string;
using BufferSet     = std::vector<std::string>;
using Size          = uint32_t;
using Id            = uint32_t;
using Offset        = uint32_t;
using DigestArray   = std::array<uint8_t, SHA256_DIGEST_LEN>;
}  // namespace plv
#endif  // PLV_TYPES_H