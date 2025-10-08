#include "jforge/constant_pool/parser.hpp"

#include <iostream>
#include <variant>

#include "jforge/constant_pool/infos.hpp"
#include "jforge/constant_pool/tags.hpp"
#include "jforge/util/file.hpp"

auto jforge::constant_pool::readPoolEntry(std::istream& stream) -> std::expected<PoolEntry, std::string>
{
    uint8_t tagNum = 0;
    stream.read(reinterpret_cast<char *>(&tagNum), sizeof(tagNum));
    const Tag tag = tagFromNum(tagNum);
    if (tag == Tag::None)
        return std::unexpected(std::format("Number {} is not a valid constant tag", tagNum));
    switch(tag) {
        case Tag::Utf8: // 1
        {
            const auto length = util::read_bytes_be<uint16_t>(stream);
            std::string bytes;
            bytes.reserve(length);
            for (int i = 0; i < length; i++) {
                char c = 0;
                stream.read(&c, sizeof(c));
                bytes +=c ;
            }
            return Utf8Info{ length, std::move(bytes) };
        }
        case Tag::Integer: // 3
            {
                const auto value = util::read_bytes_be<int32_t>(stream);
                return IntegerInfo{ value };
            }
        case Tag::Float: // 4
            {
                const auto value = util::read_bytes_be<float>(stream);
                return FloatInfo{ value };
            }
        case Tag::Long: // 5
            {
                const auto value = util::read_bytes_be<int64_t>(stream);
                return LongInfo{ value };
            }
        case Tag::Double: // 3
            {
                const auto value = util::read_bytes_be<double>(stream);
                return DoubleInfo{ value };
            }
        case Tag::Class: // 7
        {
            const auto nameIndex = util::read_bytes_be<uint16_t>(stream);
            return ClassInfo{ nameIndex };
        }
        case Tag::String: // 8
        {
            const auto stringIndex = util::read_bytes_be<uint16_t>(stream);
            return StringInfo{ stringIndex };
        }
        case Tag::Fieldref: // 9
        {
            const auto classIndex = util::read_bytes_be<uint16_t>(stream);
            const auto nameAndTypeIndex = util::read_bytes_be<uint16_t>(stream);
            return FieldrefInfo{ classIndex, nameAndTypeIndex };
        }
        case Tag::Methodref: // 10
        {
            const auto classIndex = util::read_bytes_be<uint16_t>(stream);
            const auto nameAndTypeIndex = util::read_bytes_be<uint16_t>(stream);
            return MethodrefInfo{ classIndex, nameAndTypeIndex };
        }
        case Tag::InterfaceMethodref: // 11
        {
            const auto classIndex = util::read_bytes_be<uint16_t>(stream);
            const auto nameAndTypeIndex = util::read_bytes_be<uint16_t>(stream);
            return InterfaceMethodrefInfo{ classIndex, nameAndTypeIndex };
        }
        case Tag::NameAndType: // 12
        {
            const auto nameIndex = util::read_bytes_be<uint16_t>(stream);
            const auto descriptorIndex = util::read_bytes_be<uint16_t>(stream);
            return NameAndTypeInfo { nameIndex, descriptorIndex };
        }
        default:
        {
            std::cout << "Unsupported tag: " << tagToString(tag);
            std::terminate();
        }
    }
}

auto jforge::constant_pool::readConstantPool(std::istream& stream, const uint16_t count) -> std::expected<ConstantPool, std::string>
{
    ConstantPool constantPool;
    for (uint16_t i = 0; i < count - 1; i++)
    {
        auto entry = readPoolEntry(stream);
        if (!entry)
        {
            return std::unexpected(entry.error());
        }
        constantPool.addEntry(std::move(*entry));
    }
    return constantPool;
}
