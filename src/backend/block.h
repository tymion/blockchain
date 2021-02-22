#ifndef BLOCK_H
#define BLOCK_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace model
{
constexpr auto SHA256_LEN = 32;
struct Block
{
    using Id = uint32_t;
    // HEADER
    Id id;
    std::array<uint8_t, SHA256_LEN> prevBlockHash{};
    // PAYLOAD
    std::vector<std::string> dataElements{};
};
}  // namespace model

#endif  // BLOCK_H