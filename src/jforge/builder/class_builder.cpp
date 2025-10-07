#include "jforge/builder/class_builder.hpp"

#include <fstream>

#include "jforge/builder/attribute_builder.hpp"
#include "jforge/util/file.hpp"
#include "jforge/writer/classfile_writer.hpp"
#include "jforge/writer/constant_pool_writer.hpp"

namespace jforge::builder
{
    ClassBuilder::ClassBuilder(const std::string_view name)
    {
        m_name = name;
    }

    void ClassBuilder::addMethod(MethodBuilder method)
    {
        m_methods.push_back(std::move(method));
    }

    auto ClassBuilder::emit(const std::filesystem::path& output) -> std::expected<void, std::string>
    {
        std::ofstream file{output, std::ios::binary};

        constexpr uint8_t magic[4] = {0xCA, 0xFE, 0xBA, 0xBE};
        file.write(reinterpret_cast<const char *>(magic), sizeof(magic));
        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Minor version
        util::write_bytes_be(file, static_cast<uint16_t>(65)); // Major version

        // Generate constant pool
        const auto cp = generateConstantPool();
        writer::writeConstantPool(file, cp);

        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Access flags

        const auto thisIndex = cp.getClassIndex(m_name);
        if (!thisIndex) return std::unexpected("Unable to find index of this class in constant pool");
        util::write_bytes_be(file, *thisIndex); // This class

        const auto superIndex = cp.getClassIndex("java/lang/Object");
        if (!superIndex) return std::unexpected("Unable to find index of super class in constant pool");
        util::write_bytes_be(file, *superIndex); // Super class

        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Interfaces count
        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Field count
        util::write_bytes_be(file, static_cast<uint16_t>(m_methods.size())); // Method count
        for (const auto& methodBuilder : m_methods) {
            auto method = methodBuilder.build(cp);
            if (!method)
                return std::unexpected(std::move(method.error()));
            writer::writeMethod(file, *method);
        }
        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Attributes count
        return {};
    }

    auto ClassBuilder::generateConstantPool() -> constant_pool::ConstantPool
    {
        constant_pool::ConstantPool cp;

        // Attributes
        cp.addUtf8("Code");

        // This and super class
        cp.addClass(m_name);
        cp.addClass("java/lang/Object");

        for (const auto& method : m_methods) {
            cp.addUtf8(method.getName());
            cp.addUtf8(method.getDescriptor());
            for (const auto& instruction: method.getInstructions()) {
                std::visit([&]<typename T>(const T& inst) {
                    if constexpr (std::is_same_v<T, GetStatic>) {
                        cp.addFieldref(inst.className, inst.fieldName, inst.descriptor);
                    }
                    else if constexpr (std::is_same_v<T, InvokeVirtual> || std::is_same_v<T, InvokeSpecial>) {
                        cp.addMethodref(inst.className, inst.methodName, inst.descriptor);
                    }
                    else if constexpr (std::is_same_v<T, LdcString>) {
                        cp.addString(inst.value);
                    }
                }, instruction);
            }
        }
        return cp;
    }
}
