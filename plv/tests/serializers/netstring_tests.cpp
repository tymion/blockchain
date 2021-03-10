#include <gtest/gtest.h>
#include <plv/serializers/netstring.h>
#include <string_view>

namespace
{
using namespace ::testing;
using namespace std::literals;
using namespace plv::serializers::netstring;
}  // namespace

// NOLINTNEXTLINE
TEST(NetstringTest, decodeMinimal)
{
    auto data   = "0:,"sv;
    auto result = decode(data);
    EXPECT_EQ(result.first, ""sv);
    EXPECT_EQ(result.second, 3);
}

// NOLINTNEXTLINE
TEST(NetstringTest, decode)
{
    auto data   = "1:2,10:123456789,"sv;
    auto result = decode(data);
    EXPECT_EQ(result.first, "2"sv);
    EXPECT_EQ(result.second, 4);
}

// NOLINTNEXTLINE
TEST(NetstringTest, encodeMinimal)
{
    auto data   = ""sv;
    auto result = encode(data);
    EXPECT_EQ(result, "0:,"sv);
}

// NOLINTNEXTLINE
TEST(NetstringTest, encode)
{
    auto data   = "2"sv;
    auto result = encode(data);
    EXPECT_EQ(result, "1:2,"sv);
}