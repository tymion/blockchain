#include <fmt/format.h>
#include <gtest/gtest.h>
#include <plv/dal/blockchainstorage.h>
#include <plv/dal/chunkiterator.h>
#include <plv/tests/io/mockfile.h>
#include <plv/tests/utils/utils.h>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>

namespace
{
using namespace ::testing;
using namespace std::literals;
using namespace plv;
using namespace tests::utils;
using namespace tests::io;
using namespace dal;

class BlockchainStorageTest : public Test
{
public:
    void SetUp(auto data)
    {
        EXPECT_CALL(*file_, read(_, _)).WillRepeatedly([=](auto& chunk, auto len) { chunk.assign(data.data(), len); });
        EXPECT_CALL(*file_, read(_, _, _)).WillRepeatedly([=](auto& chunk, auto offset, auto len) {
            chunk.assign(data, offset, len);
        });
        EXPECT_CALL(*file_, getSize()).WillRepeatedly(Return(data.size()));
        iter_    = std::make_shared<ChunkIterator>(file_);
        storage_ = std::make_shared<BlockchainStorage>(iter_, file_);
        storage_->indexStorage();
    }
    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    std::shared_ptr<StrictMock<MockFile>> file_{std::make_shared<StrictMock<MockFile>>()};
    std::shared_ptr<ChunkIterator> iter_{};         // NOLINT(misc-non-private-member-variables-in-classes)
    std::shared_ptr<BlockchainStorage> storage_{};  // NOLINT(misc-non-private-member-variables-in-classes)
};
}  // namespace

// NOLINTNEXTLINE
TEST_F(BlockchainStorageTest, getBlockOneShortBlock)
{
    auto data = FIRST_BLOCK_IN_NETSTRING;
    SetUp(data);
    auto blockStr = storage_->getBlock(0);
    EXPECT_EQ(blockStr, FIRST_BLOCK_STR);
    EXPECT_EQ(storage_->getChainLength(), 1);
    EXPECT_EQ(storage_->getStorageSize(), data.size());
}

// NOLINTNEXTLINE
TEST_F(BlockchainStorageTest, getBlockTwoShortBlock)
{
    auto data = FIRST_BLOCK_IN_NETSTRING + SECOND_BLOCK_IN_NETSTRING;
    SetUp(data);
    auto blockStr0 = storage_->getBlock(0);
    auto blockStr1 = storage_->getBlock(1);
    EXPECT_EQ(blockStr0, FIRST_BLOCK_STR);
    EXPECT_EQ(blockStr1, SECOND_BLOCK_STR);
    EXPECT_EQ(storage_->getChainLength(), 2);
    EXPECT_EQ(storage_->getStorageSize(), data.size());
}

// NOLINTNEXTLINE
TEST_F(BlockchainStorageTest, addBlock)
{
    EXPECT_CALL(*file_, write(_)).WillOnce([&](auto block) { EXPECT_EQ(block, SECOND_BLOCK_IN_NETSTRING); });
    SetUp(FIRST_BLOCK_IN_NETSTRING);
    EXPECT_CALL(*file_, read(_, _, _)).WillRepeatedly([=](auto& chunk, auto offset, auto len) {
        chunk.assign(SECOND_BLOCK_STR);
    });
    EXPECT_EQ(storage_->getChainLength(), 1);
    storage_->addBlock(SECOND_BLOCK_STR);
    auto blockStr = storage_->getBlock(storage_->getChainLength() - 1);
    EXPECT_EQ(blockStr, SECOND_BLOCK_STR);
    EXPECT_EQ(storage_->getChainLength(), 2);
}