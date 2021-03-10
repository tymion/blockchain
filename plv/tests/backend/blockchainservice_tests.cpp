#include <fmt/format.h>
#include <gtest/gtest.h>
#include <plv/backend/blockchainservice.h>
#include <plv/crypto/crypto.h>
#include <plv/dal/blockparser.h>
#include <plv/tests/dal/mockstorage.h>
#include <plv/tests/utils/utils.h>
#include <memory>
#include <string>
#include <string_view>

namespace
{
using namespace ::testing;
using namespace std::literals;
using namespace plv;
using namespace tests::utils;
using namespace tests::dal;
using namespace backend;

constexpr auto STORAGE_SIZE      = 69;
constexpr auto STORAGE_CHAIN_LEN = 1;

class BlockchainServiceTest : public Test
{
public:
    void SetUp() override
    {
        ON_CALL(*storage_, getChainLength()).WillByDefault(Return(STORAGE_CHAIN_LEN));
        ON_CALL(*storage_, getStorageSize()).WillByDefault(Return(FIRST_BLOCK_IN_NETSTRING.size()));
        ON_CALL(*storage_, getBlock(STORAGE_CHAIN_LEN - 1)).WillByDefault(Return(FIRST_BLOCK_STR));
        service_ = std::make_shared<BlockchainService<dal::BlockParser, crypto::Crypto>>(storage_);
    }
    std::shared_ptr<StrictMock<MockStorage>> storage_ =
        std::make_shared<StrictMock<MockStorage>>();  // NOLINT(misc-non-private-member-variables-in-classes)
    std::shared_ptr<BlockchainService<dal::BlockParser, crypto::Crypto>>
        service_{};  // NOLINT(misc-non-private-member-variables-in-classes)
};
}  // namespace

// NOLINTNEXTLINE
TEST_F(BlockchainServiceTest, getBlockById)
{
    EXPECT_CALL(*storage_, getChainLength).Times(1);
    EXPECT_CALL(*storage_, getBlock).Times(1);
    auto block = service_->getBlockById(STORAGE_CHAIN_LEN - 1);
    EXPECT_EQ(block, FIRST_BLOCK);
}

// NOLINTNEXTLINE
TEST_F(BlockchainServiceTest, getBlockByIdException)
{
    EXPECT_CALL(*storage_, getChainLength).Times(1);
    EXPECT_THROW(service_->getBlockById(STORAGE_CHAIN_LEN), std::invalid_argument);
}

// NOLINTNEXTLINE
TEST_F(BlockchainServiceTest, getDataElementFromBlockById)
{
    EXPECT_CALL(*storage_, getChainLength).Times(1);
    EXPECT_CALL(*storage_, getBlock).Times(1);
    auto element = service_->getDataElementFromBlockById(STORAGE_CHAIN_LEN - 1, FIRST_BLOCK.dataElements.size() - 1);
    EXPECT_EQ(element, FIRST_BLOCK.dataElements[FIRST_BLOCK.dataElements.size() - 1]);
}

// NOLINTNEXTLINE
TEST_F(BlockchainServiceTest, getDataElementFromBlockByIdExceptionInvalidBlockId)
{
    EXPECT_CALL(*storage_, getChainLength).Times(1);
    EXPECT_THROW(service_->getDataElementFromBlockById(STORAGE_CHAIN_LEN, FIRST_BLOCK.dataElements.size() - 1),
                 std::invalid_argument);
}

// NOLINTNEXTLINE
TEST_F(BlockchainServiceTest, getDataElementFromBlockByIdExceptionInvalidElementId)
{
    EXPECT_CALL(*storage_, getChainLength).Times(1);
    EXPECT_CALL(*storage_, getBlock).Times(1);
    EXPECT_THROW(service_->getDataElementFromBlockById(STORAGE_CHAIN_LEN - 1, FIRST_BLOCK.dataElements.size()),
                 std::invalid_argument);
}

// NOLINTNEXTLINE
TEST_F(BlockchainServiceTest, dataElementsInCache)
{
    auto elements = service_->getDataElementsFromCache();
    EXPECT_FALSE(elements.has_value());
    service_->addDataElementToCache(DATA_ELEMENT_1);
    elements = service_->getDataElementsFromCache();
    EXPECT_TRUE(elements.has_value());
    EXPECT_EQ(elements->size(), 1);
    EXPECT_EQ((*elements)[0], DATA_ELEMENT_1);
    service_->addDataElementToCache(DATA_ELEMENT_2);
    elements = service_->getDataElementsFromCache();
    EXPECT_TRUE(elements.has_value());
    EXPECT_EQ(elements->size(), 2);
    EXPECT_EQ((*elements)[0], DATA_ELEMENT_1);
    EXPECT_EQ((*elements)[1], DATA_ELEMENT_2);
}

// NOLINTNEXTLINE
TEST_F(BlockchainServiceTest, generatBlock)
{
    EXPECT_CALL(*storage_, getChainLength).Times(1);
    EXPECT_CALL(*storage_, getBlock).Times(1);
    EXPECT_CALL(*storage_, addBlock).WillOnce([&](auto block) { EXPECT_EQ(block, SECOND_BLOCK_STR); });
    service_->addDataElementToCache(DATA_ELEMENT_3);
    service_->addDataElementToCache(DATA_ELEMENT_4);
    auto block = service_->generateBlockFromCache();
    EXPECT_EQ(block, SECOND_BLOCK);
    auto elements = service_->getDataElementsFromCache();
    EXPECT_FALSE(elements.has_value());
}

// NOLINTNEXTLINE
TEST_F(BlockchainServiceTest, generatBlockException)
{
    auto elements = service_->getDataElementsFromCache();
    EXPECT_FALSE(elements.has_value());
    EXPECT_THROW(service_->generateBlockFromCache(), std::invalid_argument);
}