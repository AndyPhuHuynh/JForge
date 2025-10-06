#include "jforge/builder/class_builder.hpp"

#include <fstream>
#include <iostream>

#include "jforge/builder/attribute_builder.hpp"
#include "jforge/util/file.hpp"
#include "jforge/writer/constant_pool_writer.hpp"

namespace jforge::builder
{
    void ClassBuilder::addMethod(MethodBuilder method)
    {
        m_methods.push_back(std::move(method));
    }

    void ClassBuilder::emit(const std::filesystem::path& output)
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
        util::write_bytes_be(file, static_cast<uint16_t>(0)); // This class
        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Super class
        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Interfaces count
        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Field count
        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Method count
        util::write_bytes_be(file, static_cast<uint16_t>(0)); // Attributes count

        for (const auto& method : m_methods) {
            auto code = generateCodeAttribute(cp, method.getInstructions());
            if (!code)
                std::cerr << code.error();
        }
    }

    auto ClassBuilder::generateConstantPool() -> constant_pool::ConstantPool
    {
        constant_pool::ConstantPool cp;

        // Attributes
        cp.addUtf8("Code");

        for (const auto& method : m_methods) {
            for (const auto& instruction: method.getInstructions()) {
                std::visit([&]<typename T>(const T& inst) {
                    if constexpr (std::is_same_v<T, GetStatic>) {
                        cp.addFieldref(inst.className, inst.fieldName, inst.descriptor);
                    }
                    else if constexpr (std::is_same_v<T, InvokeVirtual>) {
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
