#include "jforge/writer/attribute_writer.hpp"

#include "jforge/util/file.hpp"

namespace jforge::writer
{
    auto writeCodeAttribute(std::ostream& os, const attributes::Code& attr) -> void
    {
        util::write_bytes_be(os, attr.maxStack);
        util::write_bytes_be(os, attr.maxLocals);
        util::write_bytes_be(os, attr.codeLength);
        os.write(reinterpret_cast<const char *>(attr.code.data()), attr.codeLength);
        util::write_bytes_be(os, attr.exceptionTableLength);
        for (const auto& [startPc, endPc, handlerPc, catchType] : attr.exceptionTable)
        {
            util::write_bytes_be(os, startPc);
            util::write_bytes_be(os, endPc);
            util::write_bytes_be(os, handlerPc);
            util::write_bytes_be(os, catchType);
        }
        util::write_bytes_be(os, attr.attributesCount);
        for (const auto& nestedAttr : attr.attributes)
        {
            writeAttribute(os, nestedAttr);
        }
    }

    auto writeAttribute(std::ostream& os, const attributes::AttributeInfo& attr) -> void
    {
        util::write_bytes_be(os, attr.nameIndex);
        util::write_bytes_be(os, attr.length);
        std::visit([&os]<typename T>(const T& value) {
            if constexpr (std::is_same_v<T, attributes::Code>) {
                writeCodeAttribute(os, value);
            }
        }, attr.value);
    }
}
