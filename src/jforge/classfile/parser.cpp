#include "jforge/classfile/parser.hpp"

#include "jforge/attributes/parser.hpp"
#include "jforge/util/file.hpp"

auto jforge::classfile::readMethodInfo(
    std::istream& stream,
    const constant_pool::ConstantPool& cp) -> std::expected<MethodInfo, std::string>
{
    MethodInfo info;
    info.accessFlags     = util::read_bytes_be<uint16_t>(stream);
    info.nameIndex       = util::read_bytes_be<uint16_t>(stream);
    info.descriptorIndex = util::read_bytes_be<uint16_t>(stream);
    info.attributeCounts = util::read_bytes_be<uint16_t>(stream);
    info.attributes.reserve(info.attributeCounts);
    for (uint16_t i = 0; i < info.attributeCounts; i++)
    {
        auto attr = attributes::readAttribute(stream, cp);
        if (!attr)
            return std::unexpected(attr.error());
        info.attributes.emplace_back(std::move(*attr));
    }
    return info;
}
