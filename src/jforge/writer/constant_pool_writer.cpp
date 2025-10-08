#include "jforge/writer/constant_pool_writer.hpp"

#include <iostream>

#include "jforge/constant_pool/infos.hpp"
#include "jforge/constant_pool/tags.hpp"
#include "jforge/util/file.hpp"

namespace jforge::writer
{
    auto writeConstantPoolEntry(std::ostream& os, const constant_pool::PoolEntry& entry) -> void
    {
        std::visit([&os]<typename T>(const T& e) {
            auto tag = constant_pool::tagFromType<T>();
            if (tag == constant_pool::Tag::None)
            {
                std::cerr << "Unknown type while writing entry" << std::endl;
                return;
            }
            os << constant_pool::tagToNum(tag);
            if constexpr (std::is_same_v<T, constant_pool::Utf8Info>)
            {
                util::write_bytes_be(os, e.length);
                os.write(e.bytes.data(), e.length);
            }
            else if constexpr (
                std::is_same_v<T, constant_pool::IntegerInfo> ||
                std::is_same_v<T, constant_pool::FloatInfo> ||
                std::is_same_v<T, constant_pool::LongInfo> ||
                std::is_same_v<T, constant_pool::DoubleInfo>)
            {
                util::write_bytes_be(os, e.value);
            }
            else if constexpr (std::is_same_v<T, constant_pool::ClassInfo>)
            {
                util::write_bytes_be(os, e.nameIndex);
            }
            else if constexpr (std::is_same_v<T, constant_pool::StringInfo>)
            {
                util::write_bytes_be(os, e.stringIndex);
            }
            else if constexpr (
                std::is_same_v<T, constant_pool::FieldrefInfo> ||
                std::is_same_v<T, constant_pool::MethodrefInfo> ||
                std::is_same_v<T, constant_pool::InterfaceMethodrefInfo>)
            {
                util::write_bytes_be(os, e.classIndex);
                util::write_bytes_be(os, e.nameAndTypeIndex);
            }
            else if constexpr (std::is_same_v<T, constant_pool::NameAndTypeInfo>)
            {
                util::write_bytes_be(os, e.nameIndex);
                util::write_bytes_be(os, e.descriptorIndex);
            }
        }, entry);
    }

    auto writeConstantPool(std::ostream& os, const constant_pool::ConstantPool& cp) -> void
    {
        const uint16_t cpCount = cp.size();
        util::write_bytes_be(os, cpCount);
        for (const auto& entry : cp.realEntries())
        {
            writeConstantPoolEntry(os, entry);
        }
    }
}
