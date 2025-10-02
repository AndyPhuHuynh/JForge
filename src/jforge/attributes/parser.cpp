#include "jforge/attributes/parser.hpp"

#include <iostream>

#include "jforge/util/file.hpp"

auto jforge::attributes::readCode(
    std::istream& stream,
    const constant_pool::ConstantPool& cp) -> std::expected<Code, std::string>
{
    Code code;
    code.maxStack = util::read_bytes_be<uint16_t>(stream);
    code.maxLocals = util::read_bytes_be<uint16_t>(stream);
    code.codeLength = util::read_bytes_be<uint32_t>(stream);
    code.code.reserve(code.codeLength);
    for (uint32_t i = 0; i < code.codeLength; i++)
    {
        code.code.emplace_back(util::read_bytes_be<uint8_t>(stream));
    }
    code.exceptionTableLength = util::read_bytes_be<uint16_t>(stream);
    for (uint16_t i = 0; i < code.exceptionTableLength; i++)
    {
        ExceptionTableEntry entry{};
        entry.startPc   = util::read_bytes_be<uint16_t>(stream);
        entry.endPc     = util::read_bytes_be<uint16_t>(stream);
        entry.handlerPc = util::read_bytes_be<uint16_t>(stream);
        entry.catchType = util::read_bytes_be<uint16_t>(stream);
    }
    code.attributesCount = util::read_bytes_be<uint16_t>(stream);
    for (uint16_t i = 0; i < code.attributesCount; i++)
    {
        auto attr = readAttribute(stream, cp);
        if (!attr)
            return std::unexpected(attr.error());
        code.attributes.emplace_back(std::move(*attr));
    }
    return code;
}

auto jforge::attributes::readLineNumberTable(std::istream& stream) -> LineNumberTable
{
    LineNumberTable table;
    table.length = util::read_bytes_be<uint16_t>(stream);
    table.entries.reserve(table.length);
    for (uint16_t i = 0; i < table.length; i++)
    {
        auto& [startPc, lineNumber] = table.entries.emplace_back();
        startPc    = util::read_bytes_be<uint16_t>(stream);
        lineNumber = util::read_bytes_be<uint16_t>(stream);
    }
    return table;
}

auto jforge::attributes::readAttribute( // NOLINT (misc-no-recursion)
    std::istream& stream,
    const constant_pool::ConstantPool& cp) -> std::expected<AttributeInfo, std::string>
{
    AttributeInfo attr{};
    attr.nameIndex = util::read_bytes_be<uint16_t>(stream);
    attr.length    = util::read_bytes_be<uint32_t>(stream);

    const auto type = cp.getUtf8(attr.nameIndex);
    if (!type)
        return std::unexpected(type.error());

    std::cout << "Attribute type: " << *type << "\n";
    if (type == "Code")
    {
        auto code = readCode(stream, cp);
        if (!code)
            return std::unexpected(code.error());
        attr.value = std::move(*code);
    }
    else if (type == "LineNumberTable")
    {
        attr.value = readLineNumberTable(stream);
    }
    else
    {
        std::cerr << "Unsupported attribute type: " << *type << "\n";
        std::terminate();
    }
    return attr;
}
