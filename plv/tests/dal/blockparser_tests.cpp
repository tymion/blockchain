#include <fmt/format.h>
#include <gtest/gtest.h>
#include <plv/dal/blockparser.h>
#include <string>

namespace
{
using namespace ::testing;
using namespace plv::dal;

constexpr std::array<uint8_t, 32> HASH{'0', '0', '5', '0', '0', '0', '4', '0', '0', '0', '0', '3', '0', '0', '0', '0',
                                       '0', '0', '0', '0', '0', '0', '0', '0', '0', '2', '0', '0', '0', '0', '0', '1'};

constexpr auto DATA_ELEMENT_1 = "DataElement1";
constexpr auto DATA_ELEMENT_2 = "DataElement10";

}  // namespace

// NOLINTNEXTLINE
TEST(BlockParserTest, deserializeBlock)
{
    datamodel::Block block = {.prevBlockHash = HASH, .dataElements = {DATA_ELEMENT_1, DATA_ELEMENT_2}};

    auto hash              = std::string(std::begin(block.prevBlockHash), std::end(block.prevBlockHash));
    auto blockStr          = fmt::format("32:{},{}:{},{}:{},", hash, strlen(DATA_ELEMENT_1), DATA_ELEMENT_1,
                                strlen(DATA_ELEMENT_2), DATA_ELEMENT_2);
    auto blockDeserialized = BlockParser::deserialize(blockStr);
    EXPECT_EQ(blockDeserialized.prevBlockHash, block.prevBlockHash);
    EXPECT_EQ(blockDeserialized.dataElements.size(), 2);
    EXPECT_EQ(blockDeserialized.dataElements[0], DATA_ELEMENT_1);
    EXPECT_EQ(blockDeserialized.dataElements[1], DATA_ELEMENT_2);
    auto blockSerialized = BlockParser::serialize(blockDeserialized);
    EXPECT_EQ(blockSerialized, blockStr);
}