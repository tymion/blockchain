#ifndef DATAMODEL_BLOCK_H
#define DATAMODEL_BLOCK_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace datamodel
{
constexpr auto SHA256_LEN = 32;
using SHA256Array         = std::array<uint8_t, SHA256_LEN>;

struct Block
{
    SHA256Array prevBlockHash{};
    // PAYLOAD
    std::vector<std::string> dataElements{};
};

inline bool operator==(const Block& lhs, const Block& rhs)
{
    return lhs.prevBlockHash == rhs.prevBlockHash && lhs.dataElements == rhs.dataElements;
}

}  // namespace datamodel

#endif  // DATAMODEL_BLOCK_H