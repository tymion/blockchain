#include <ctime>
#include "crypto.h"

using namespace plv::crypto;

auto Crypto::sha256(BufferView input, DigestArray& output) -> void
{
    using namespace std;
    for (auto i = 0; i < output.size(); i++)
    {
        for (auto j = 0; j <= i; j++)
        {
            output[i] += input[j];
        }
        output[i] /= 3;
    }
}