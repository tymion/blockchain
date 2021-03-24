#ifndef PLV_TESTS_UTILS_UTILS_H
#define PLV_TESTS_UTILS_UTILS_H
#include <fmt/format.h>
#include <plv/datamodel/block.h>
#include <array>
#include <string_view>

namespace plv::tests::utils
{
constexpr std::string_view DATA_ELEMENT_1 = "DataElement1";
constexpr std::string_view DATA_ELEMENT_2 = "DataElement10";
constexpr std::string_view DATA_ELEMENT_3 = "DataElemento3";
constexpr std::string_view DATA_ELEMENT_4 = "DataElemento4";

constexpr DigestArray FIRST_HASH{0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
                                 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

constexpr auto FIRST_HASH_SV = std::string_view{
    "00000500000004000000"
    "00030000000000000000"
    "00000000000200000000"
    "0001"};

datamodel::Block FIRST_BLOCK = {.prevBlockHash = FIRST_HASH,
                                .dataElements  = {std::string(DATA_ELEMENT_1), std::string(DATA_ELEMENT_2)}};

auto FIRST_BLOCK_STR = fmt::format("{}:{},{}:{},{}:{},", FIRST_HASH_SV.size(), FIRST_HASH_SV, DATA_ELEMENT_1.size(),
                                   DATA_ELEMENT_1, DATA_ELEMENT_2.size(), DATA_ELEMENT_2);

constexpr DigestArray SECOND_HASH{0xc9, 0xcb, 0xc5, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xca, 0xcf, 0xcf,
                                  0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcb, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf,
                                  0xcf, 0xcf, 0xcf, 0xcf, 0xcc, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf};

constexpr auto SECOND_HASH_SV = std::string_view{
    "c9cbc5cfcfcfcfcfcacf"
    "cfcfcfcfcfcfcbcfcfcf"
    "cfcfcfcfcccfcfcfcdcf"
    "cfcf"};

datamodel::Block SECOND_BLOCK = {.prevBlockHash = SECOND_HASH,
                                 .dataElements  = {std::string(DATA_ELEMENT_3), std::string(DATA_ELEMENT_4)}};

auto SECOND_BLOCK_STR =
    fmt::format("{}:{},{}:{},{}:{},", SECOND_HASH.size(), std::string{std::begin(SECOND_HASH), std::end(SECOND_HASH)},
                DATA_ELEMENT_3.size(), DATA_ELEMENT_3, DATA_ELEMENT_4.size(), DATA_ELEMENT_4);

auto FIRST_BLOCK_LENGTH        = FIRST_BLOCK_STR.size();
auto SECOND_BLOCK_LENGTH       = SECOND_BLOCK_STR.size();
auto SECOND_BLOCK_OFFSET       = 76;
auto FIRST_BLOCK_IN_NETSTRING  = fmt::format("{}:{},", FIRST_BLOCK_LENGTH, FIRST_BLOCK_STR);
auto SECOND_BLOCK_IN_NETSTRING = fmt::format("{}:{},", SECOND_BLOCK_LENGTH, SECOND_BLOCK_STR);

}  // namespace plv::tests::utils

#endif  // PLV_TESTS_UTILS_UTILS_H