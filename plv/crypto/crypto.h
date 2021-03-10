#ifndef PLV_CRYPTO_CRYPTO_H
#define PLV_CRYPTO_CRYPTO_H

#include <array>
#include <cstdint>
#include <string_view>

namespace plv::crypto
{
constexpr auto SHA256_DIGEST_LEN = 32;

class Crypto
{
public:
    using DigestArray = std::array<uint8_t, SHA256_DIGEST_LEN>;
    using BufferView  = std::string_view;

    static auto sha256(BufferView, DigestArray&) -> void;
};
}  // namespace plv::crypto
#endif  // PLV_CRYPTO_CRYPTO_H