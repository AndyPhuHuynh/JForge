#include "jforge/classfile/parser.hpp"

#include "jforge/attributes/reader.hpp"
#include "jforge/constant_pool/parser.hpp"
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

auto jforge::classfile::readClassFile(std::istream& stream) -> std::expected<ClassFile, std::string>
{
    ClassFile file{};
    char magic[4];
    stream.read(magic, std::size(magic));
    if (magic[0] != 0xCA || magic[1] != 0xFE || magic[2] != 0xBA || magic[3] != 0xBE)
        return std::unexpected(std::format(R"(Magic value "{}" does not match 0xCAFEBABE)", util::formatHex(magic)));

    file.minorVersion = jforge::util::read_bytes_be<uint16_t>(stream);
    file.majorVersion = jforge::util::read_bytes_be<uint16_t>(stream);

    const auto constantPoolCount = jforge::util::read_bytes_be<uint16_t>(stream);
    auto pool = constant_pool::readConstantPool(stream, constantPoolCount);
    if (!pool) return std::unexpected(std::format("Unable to read constant pool: {}", pool.error()));
    file.constantPool = std::move(*pool);

    file.accessFlags = jforge::util::read_bytes_be<uint16_t>(stream);
    file.thisClass   = jforge::util::read_bytes_be<uint16_t>(stream);
    file.superClass  = jforge::util::read_bytes_be<uint16_t>(stream);

    const auto interfacesCount = jforge::util::read_bytes_be<uint16_t>(stream);
    if (interfacesCount > 0) return std::unexpected("Interfaces not yet supported\n");

    const auto fieldsCount = jforge::util::read_bytes_be<uint16_t>(stream);
    if (fieldsCount > 0) return std::unexpected("Fields not yet supported\n");

    const auto methodsCount = jforge::util::read_bytes_be<uint16_t>(stream);
    file.methods.reserve(methodsCount);
    for (uint16_t i = 0; i < methodsCount; i++)
    {
        auto method = readMethodInfo(stream, file.constantPool);
        if (!method) return std::unexpected(std::format("Unable to read method: {}", method.error()));
        file.methods.emplace_back(std::move(*method));
    }

    const auto attributesCount = jforge::util::read_bytes_be<uint16_t>(stream);
    for (uint16_t i = 0; i < attributesCount; i++)
    {
        auto attr = attributes::readAttribute(stream, file.constantPool);
        if (!attr) return std::unexpected(std::format("Unable to read attributes: {}", attr.error()));
        file.attributes.emplace_back(std::move(*attr));
    }
    return file;
}
