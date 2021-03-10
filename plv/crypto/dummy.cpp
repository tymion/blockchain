#include "crypto.h"

using namespace plv::crypto;

auto Crypto::sha256(BufferView input, DigestArray& output) -> void
{
    using namespace std;
    transform(begin(input), begin(input) + output.size(), std::begin(output),
              [](const auto& sign) { return sign ^ 0xFF; });
}