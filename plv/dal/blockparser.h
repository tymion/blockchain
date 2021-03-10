#ifndef PLV_DAL_BLOCK_PARSER_H
#define PLV_DAL_BLOCK_PARSER_H

#include <plv/datamodel/block.h>
#include <plv/serializers/netstring.h>
#include <algorithm>
#include <charconv>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

namespace plv::dal
{
class BlockParser
{
public:
    using Size       = uint32_t;
    using Offset     = uint32_t;
    using Buffer     = std::string;
    using BufferView = std::string_view;

    static auto deserialize(BufferView data) -> datamodel::Block
    {
        using namespace serializers::netstring;
        using namespace std;
        datamodel::Block block{};
        auto consumed = parseHash(block, data);
        while (consumed < data.length())
        {
            consumed += parseDataElement(block, data.substr(consumed));
        }
        return block;
    }

    static auto serialize(datamodel::Block block) -> Buffer
    {
        using namespace serializers::netstring;
        std::string elements{};
        for (const auto& element : block.dataElements)
        {
            elements = fmt::format("{}{}", elements, encode(element));
        }
        auto hash = std::string(std::begin(block.prevBlockHash), std::end(block.prevBlockHash));
        return fmt::format("{}{}", encode(hash), elements);
    }

private:
    static auto parseHash(datamodel::Block& block, BufferView data) -> Size
    {
        using namespace serializers::netstring;
        using namespace std;
        auto [hash, consumed] = decode(data);
        copy(begin(hash), end(hash), block.prevBlockHash.data());
        return consumed;
    }

    static auto parseDataElement(datamodel::Block& block, BufferView data) -> Size
    {
        using namespace serializers::netstring;
        using namespace std;
        auto [dataElement, consumed] = decode(data);
        block.dataElements.emplace_back(Buffer(dataElement));
        return consumed;
    }
};
}  // namespace plv::dal

#endif  // PLV_DAL_BLOCK_PARSER_H