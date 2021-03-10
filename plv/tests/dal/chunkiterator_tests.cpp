#include <gtest/gtest.h>
#include <plv/dal/chunkiterator.h>
#include <plv/tests/io/mockfile.h>
#include <memory>
#include <string>
#include <string_view>

namespace
{
using namespace ::testing;
using namespace std::literals;
using namespace plv;
using namespace tests::io;
using namespace dal;

class ChunkIteratorTest : public Test
{
public:
    std::shared_ptr<StrictMock<MockFile>> file_{std::make_shared<StrictMock<MockFile>>()};
};
}  // namespace

// NOLINTNEXTLINE
TEST_F(ChunkIteratorTest, getNextWithDataLessThanOneChunk)
{
    constexpr auto DATA_SIZE = 100;
    auto data                = std::string(DATA_SIZE, 1);
    EXPECT_CALL(*file_, getSize()).Times(2).WillRepeatedly(Return(data.length()));
    EXPECT_CALL(*file_, read(_, _)).WillOnce([&](auto& chunk, [[maybe_unused]] auto len) { chunk.assign(data); });

    auto iterator{std::make_unique<ChunkIterator>(file_)};
    auto chunkOpt = iterator->getNext();
    EXPECT_TRUE(chunkOpt.has_value());
    EXPECT_EQ(chunkOpt->getData(), std::string_view{data});
    chunkOpt = iterator->getNext();
    EXPECT_FALSE(chunkOpt.has_value());
}

// NOLINTNEXTLINE
TEST_F(ChunkIteratorTest, getNextWithDataMoreThanOneChunk)
{
    constexpr auto DATA_SIZE = CHUNK_SIZE + 1;
    auto data                = std::string(DATA_SIZE, 1);
    EXPECT_CALL(*file_, getSize()).WillRepeatedly(Return(data.length()));
    EXPECT_CALL(*file_, read(_, _)).Times(2).WillRepeatedly([&](auto& chunk, auto len) { chunk.assign(data, 0, len); });

    auto iterator{std::make_unique<ChunkIterator>(file_)};
    auto chunkOpt = iterator->getNext();
    EXPECT_TRUE(chunkOpt.has_value());
    EXPECT_EQ(chunkOpt->getData(), std::string_view{data}.substr(0, CHUNK_SIZE));
    chunkOpt = iterator->getNext();
    EXPECT_TRUE(chunkOpt.has_value());
    EXPECT_EQ(chunkOpt->getData(), std::string_view{data}.substr(0, 1));
    chunkOpt = iterator->getNext();
    EXPECT_FALSE(chunkOpt.has_value());
}