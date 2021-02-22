#include <backend/blockchainstorage.h>
#include <backend/chunkiterator.h>
#include <gtest/gtest.h>
#include <io/mockfile.h>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>

namespace
{
using namespace ::testing;
using namespace std::literals;
using namespace io::tests;
using namespace backend;

constexpr auto FIRST_BLOCK_IN_NETSTRING = "69:32:00000000000000000000000000000000,12:DataElement1,13:DataElement10,,";
constexpr auto SHORT_BLOCK_IN_NETSTRING = "69:32:1234567890abcdef1234567890abcdef,12:DataElement2,13:DataElement20,,";

class BlockchainStorageTest : public Test
{
public:
    void SetUp(auto data)
    {
        EXPECT_CALL(*file_, read(_, _)).WillRepeatedly([=](auto& chunk, auto len) { chunk.assign(data, len); });
        EXPECT_CALL(*file_, getSize()).WillRepeatedly(Return(strlen(data)));
        iter_    = std::make_shared<ChunkIterator>(file_);
        storage_ = std::make_shared<BlockchainStorage>(iter_, file_);
    }
    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    std::shared_ptr<StrictMock<MockFile>> file_{std::make_shared<StrictMock<MockFile>>()};
    std::shared_ptr<ChunkIterator> iter_{};         // NOLINT(misc-non-private-member-variables-in-classes)
    std::shared_ptr<BlockchainStorage> storage_{};  // NOLINT(misc-non-private-member-variables-in-classes)
};
}  // namespace

// NOLINTNEXTLINE
TEST_F(BlockchainStorageTest, getMetaBlocksOneShortBlock)
{
    SetUp(FIRST_BLOCK_IN_NETSTRING);
    auto metaBlockVector = storage_->getMetaBlocks();
    EXPECT_EQ(metaBlockVector.size(), 1);
    EXPECT_EQ(metaBlockVector[0], (model::MetaBlock{3, 69}));
}

// NOLINTNEXTLINE
TEST_F(BlockchainStorageTest, getMetaBlocksTwoShortBlock)
{
    auto data = std::string{FIRST_BLOCK_IN_NETSTRING} + std::string{SHORT_BLOCK_IN_NETSTRING};
    SetUp(data.c_str());
    auto metaBlockVector = storage_->getMetaBlocks();
    EXPECT_EQ(metaBlockVector.size(), 2);
    EXPECT_EQ(metaBlockVector[0], (model::MetaBlock{3, 69}));
    EXPECT_EQ(metaBlockVector[1], (model::MetaBlock{73 + 3, 69}));
}
