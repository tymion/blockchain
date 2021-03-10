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

constexpr datamodel::SHA256Array FIRST_HASH{'0', '0', '5', '0', '0', '0', '4', '0', '0', '0', '0',
                                            '3', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                                            '0', '0', '0', '2', '0', '0', '0', '0', '0', '1'};

datamodel::Block FIRST_BLOCK = {.prevBlockHash = FIRST_HASH,
                                .dataElements  = {std::string(DATA_ELEMENT_1), std::string(DATA_ELEMENT_2)}};

auto FIRST_BLOCK_STR =
    fmt::format("{}:{},{}:{},{}:{},", FIRST_HASH.size(), std::string{std::begin(FIRST_HASH), std::end(FIRST_HASH)},
                DATA_ELEMENT_1.size(), DATA_ELEMENT_1, DATA_ELEMENT_2.size(), DATA_ELEMENT_2);

constexpr datamodel::SHA256Array SECOND_HASH{0xcc, 0xcd, 0xc5, 0xcf, 0xcf, 0xca, 0xcf, 0xcf, 0xcf, 0xcb, 0xcf,
                                             0xcf, 0xcf, 0xcf, 0xcc, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf,
                                             0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcd, 0xcf, 0xcf, 0xcf};

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