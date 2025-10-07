#include "jforge/builder/attribute_builder.hpp"

#include <iostream>
#include <limits>

#include "jforge/opcode.hpp"
#include "jforge/util/vector.hpp"

namespace jforge::builder
{
    auto generateCodeAttribute(
        const constant_pool::ConstantPool& cp,
        const std::vector<Instructions>& instructions) -> std::expected<attributes::Code, std::string>
    {
        attributes::Code attr;

        // TODO: Un-hardcode these values
        attr.maxStack = 100;
        attr.maxLocals = 100;

        for (const auto& instruction : instructions)
        {
            auto errorMsg = std::visit([&]<typename T>(const T& inst) -> std::string {
                if constexpr (std::is_same_v<T, LdcString>) {
                    const auto strIndex = cp.getStringIndex(inst.value);
                    if (!strIndex) return strIndex.error();
                    if (*strIndex <= std::numeric_limits<uint8_t>::max()) {
                        attr.code.push_back(static_cast<uint8_t>(OpCode::ldc));
                        util::push_back_be(attr.code, static_cast<uint8_t>(strIndex.value()));
                    } else
                    {
                        attr.code.push_back(static_cast<uint8_t>(OpCode::ldc_w));
                        util::push_back_be(attr.code, static_cast<uint16_t>(strIndex.value()));
                    }
                }
                else if constexpr (std::is_same_v<T, ALoad0>) {
                    attr.code.push_back(static_cast<uint8_t>(OpCode::aload_0));
                }
                else if constexpr (std::is_same_v<T, ALoad1>) {
                    attr.code.push_back(static_cast<uint8_t>(OpCode::aload_1));
                }
                else if constexpr (std::is_same_v<T, ALoad2>) {
                    attr.code.push_back(static_cast<uint8_t>(OpCode::aload_2));
                }
                else if constexpr (std::is_same_v<T, ALoad3>) {
                    attr.code.push_back(static_cast<uint8_t>(OpCode::aload_3));
                }
                else if constexpr (std::is_same_v<T, Ret>) {
                    attr.code.push_back(static_cast<uint8_t>(OpCode::ret));
                }
                else if constexpr (std::is_same_v<T, GetStatic>) {
                    attr.code.push_back(static_cast<uint8_t>(OpCode::getstatic));
                    const auto fieldIndex = cp.getFieldrefIndex(inst.className, inst.fieldName, inst.descriptor);
                    if (!fieldIndex) return fieldIndex.error();
                    util::push_back_be(attr.code, static_cast<uint16_t>(fieldIndex.value()));
                }
                else if constexpr (std::is_same_v<T, InvokeVirtual>) {
                    attr.code.push_back(static_cast<uint8_t>(OpCode::invokevirtual));
                    const auto methodIndex = cp.getMethodrefIndex(inst.className, inst.methodName, inst.descriptor);
                    if (!methodIndex) return methodIndex.error();
                    util::push_back_be(attr.code, static_cast<uint16_t>(methodIndex.value()));
                }
                else if constexpr (std::is_same_v<T, InvokeSpecial>) {
                    attr.code.push_back(static_cast<uint8_t>(OpCode::invokespecial));
                    const auto methodIndex = cp.getMethodrefIndex(inst.className, inst.methodName, inst.descriptor);
                    if (!methodIndex) return methodIndex.error();
                    util::push_back_be(attr.code, static_cast<uint16_t>(methodIndex.value()));
                }
                else {
                    std::cerr << "Unsupported instruction type" << std::endl;
                    std::terminate();
                }
                return "";
            }, instruction);
            if (!errorMsg.empty())
                return std::unexpected(errorMsg);
        }
        attr.codeLength = attr.code.size();

        attr.exceptionTableLength = 0;
        attr.attributesCount = 0;
        return attr;
    }
}
