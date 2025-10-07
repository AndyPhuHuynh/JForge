#include "jforge/writer/classfile_writer.hpp"

#include "jforge/util/file.hpp"
#include "jforge/writer/attribute_writer.hpp"

namespace jforge::writer
{
    auto writeMethod(std::ostream& os, const classfile::MethodInfo& method) -> void
    {
        util::write_bytes_be(os, method.accessFlags);
        util::write_bytes_be(os, method.nameIndex);
        util::write_bytes_be(os, method.descriptorIndex);
        util::write_bytes_be(os, method.attributeCounts);
        for (const auto& attr : method.attributes) {
            writeAttribute(os, attr);
        }
    }
}
