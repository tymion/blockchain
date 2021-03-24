#ifndef PLV_DAL_BLOCK_PARSER_H
#define PLV_DAL_BLOCK_PARSER_H

#include <plv/datamodel/block.h>
#include <plv/serializers/netstring.h>
#include <plv/types.h>
#include <algorithm>
#include <charconv>
#include <iomanip>
#include <sstream>

namespace plv::dal
{
class BlockParser
{
public:
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
        using namespace std;
        string elements{};
        for (const auto& element : block.dataElements)
        {
            elements = fmt::format("{}{}", elements, encode(element));
        }
        stringstream sstream;
        sstream << hex << setw(2) << setfill('0');
        for_each(begin(block.prevBlockHash), end(block.prevBlockHash),
                 [&](auto& item) { sstream << hex << setw(2) << setfill('0') << (int)item; });
        return fmt::format("{}{}", encode(sstream.str()), elements);
    }

private:
    static auto parseHash(datamodel::Block& block, BufferView data) -> Size
    {
        using namespace serializers::netstring;
        using namespace std;
        auto [hash, consumed] = decode(data);
        for (auto i = 0; i < hash.size(); i += 2)
        {
            auto bufferView = hash.substr(i, 2);
            from_chars(begin(bufferView), end(bufferView), block.prevBlockHash[i / 2], 16);
        }
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