#ifndef PLV_CRYPTO_CRYPTO_H
#define PLV_CRYPTO_CRYPTO_H

#include <plv/types.h>

namespace plv::crypto
{
class Crypto
{
public:
    static auto sha256(BufferView, DigestArray&) -> void;
};
}  // namespace plv::crypto
#endif  // PLV_CRYPTO_CRYPTO_H