#include "jforge/writer/classfile_writer.hpp"

#include "jforge/util/file.hpp"
#include "jforge/writer/attribute_writer.hpp"
#include "jforge/writer/constant_pool_writer.hpp"

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

    auto writeClassFile(std::ostream& os, const classfile::ClassFile& classFile) -> void
    {
        constexpr uint8_t magic[4] = {0xCA, 0xFE, 0xBA, 0xBE};
        os.write(reinterpret_cast<const char *>(magic), sizeof(magic));
        util::write_bytes_be(os, static_cast<uint16_t>(0)); // Minor version
        util::write_bytes_be(os, static_cast<uint16_t>(65)); // Major version

        writeConstantPool(os, classFile.constantPool);

        util::write_bytes_be(os, static_cast<uint16_t>(0)); // Access flags
        util::write_bytes_be(os, classFile.thisClass); // This class
        util::write_bytes_be(os, classFile.superClass); // Super class

        util::write_bytes_be(os, static_cast<uint16_t>(0)); // Interfaces count
        util::write_bytes_be(os, static_cast<uint16_t>(0)); // Field count
        util::write_bytes_be(os, static_cast<uint16_t>(classFile.methods.size())); // Method count
        for (const auto& method : classFile.methods) {
            writeMethod(os, method);
        }
        util::write_bytes_be(os, static_cast<uint16_t>(0)); // Attributes count
    }
}
