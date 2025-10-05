#pragma once

#include <vector>

#include "jforge/builder/method_builder.hpp"
#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::builder
{
    class ClassBuilder
    {
        std::vector<MethodBuilder> methods;

        void emit()
        {
            // std::ofstream file{output, std::ios::binary};
            //
            // file << 0xCA << 0xFE << 0xBA << 0xBE;
            //
            // util::write_bytes_be(file, static_cast<uint16_t>(0)); // Minor version
            // util::write_bytes_be(file, static_cast<uint16_t>(65)); // Major version

            // Generate constant pool
            auto cp = generateConstantPool();
        };

        auto generateConstantPool() -> constant_pool::ConstantPool
        {
            constant_pool::ConstantPool cp;
            for (const auto& method : methods)
            {
                for (const auto& instruction: method.getInstructions())
                {
                    std::visit([&]<typename T>(const T& inst) {
                        if constexpr (std::is_same_v<T, GetStatic>)
                        {
                            cp.addFieldref(inst.className, inst.fieldName, inst.descriptor);
                        }
                        else if constexpr (std::is_same_v<T, InvokeVirtual>)
                        {
                            cp.addMethodref(inst.className, inst.methodName, inst.descriptor);
                        }
                        else if constexpr (std::is_same_v<T, LdcString>)
                        {
                            cp.addString(inst.value);
                        }
                    }, instruction);
                }
            }
            return cp;
        }

        auto writeConstantPool()
    };
}
