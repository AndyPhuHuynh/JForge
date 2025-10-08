#include "jforge/builder/attribute_builder.hpp"

#include <iostream>
#include <limits>

#include "../../../include/jforge/bytecode/opcode.hpp"
#include "jforge/util/vector.hpp"

namespace jforge::builder
{
    auto generateCodeAttribute(
        const constant_pool::ConstantPool& cp,
        const std::vector<bytecode::Instructions>& instructions) -> std::expected<attributes::Code, std::string>
    {
        attributes::Code attr;

        // TODO: Un-hardcode these values
        attr.maxStack = 100;
        attr.maxLocals = 100;

        for (const auto& instruction : instructions)
        {
            auto errorMsg = std::visit([&]<typename T>(const T& inst) -> std::string {
                if constexpr (std::is_same_v<T, bytecode::InstructionOneArgInt8>) {
                    attr.code.push_back(static_cast<uint8_t>(inst.opcode));
                    util::push_back_be(attr.code, inst.value);
                }
                if constexpr (std::is_same_v<T, bytecode::InstructionOneArgInt8>) {
                    attr.code.push_back(static_cast<uint8_t>(inst.opcode));
                    util::push_back_be(attr.code, inst.value);
                }
                if constexpr (std::is_same_v<T, bytecode::InstructionOneArgInt16>) {
                    attr.code.push_back(static_cast<uint8_t>(inst.opcode));
                    util::push_back_be(attr.code, inst.value);
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionLdcInt>) {
                    const auto intIndex = cp.getIntIndex(inst.value);
                    if (!intIndex) return intIndex.error();
                    if (*intIndex <= std::numeric_limits<uint8_t>::max()) {
                        attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc));
                        util::push_back_be(attr.code, static_cast<uint8_t>(intIndex.value()));
                    } else
                    {
                        attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc_w));
                        util::push_back_be(attr.code, static_cast<uint16_t>(intIndex.value()));
                    }
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionLdcFloat>) {
                    const auto floatIndex = cp.getFloatIndex(inst.value);
                    if (!floatIndex) return floatIndex.error();
                    if (*floatIndex <= std::numeric_limits<uint8_t>::max()) {
                        attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc));
                        util::push_back_be(attr.code, static_cast<uint8_t>(floatIndex.value()));
                    } else
                    {
                        attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc_w));
                        util::push_back_be(attr.code, static_cast<uint16_t>(floatIndex.value()));
                    }
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionLdcLong>) {
                    const auto longIndex = cp.getLongIndex(inst.value);
                    if (!longIndex) return longIndex.error();
                    attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc2_w));
                    util::push_back_be(attr.code, static_cast<uint16_t>(longIndex.value()));
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionLdcDouble>) {
                    const auto doubleIndex = cp.getDoubleIndex(inst.value);
                    if (!doubleIndex) return doubleIndex.error();
                    attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc2_w));
                    util::push_back_be(attr.code, static_cast<uint16_t>(doubleIndex.value()));
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionLdcClass>) {
                    const auto classIndex = cp.getClassIndex(inst.className);
                    if (!classIndex) return classIndex.error();
                    if (*classIndex <= std::numeric_limits<uint8_t>::max()) {
                        attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc));
                        util::push_back_be(attr.code, static_cast<uint8_t>(classIndex.value()));
                    } else
                    {
                        attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc_w));
                        util::push_back_be(attr.code, static_cast<uint16_t>(classIndex.value()));
                    }
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionLdcString>) {
                    const auto strIndex = cp.getStringIndex(inst.value);
                    if (!strIndex) return strIndex.error();
                    if (*strIndex <= std::numeric_limits<uint8_t>::max()) {
                        attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc));
                        util::push_back_be(attr.code, static_cast<uint8_t>(strIndex.value()));
                    } else
                    {
                        attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::ldc_w));
                        util::push_back_be(attr.code, static_cast<uint16_t>(strIndex.value()));
                    }
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionIINC>) {
                    attr.code.push_back(static_cast<uint8_t>(bytecode::OpCode::iinc));
                    util::push_back_be(attr.code, inst.index);
                    util::push_back_be(attr.code, inst.increment);
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionNoArg>) {
                    attr.code.push_back(static_cast<uint8_t>(inst.opcode));
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionFieldArg>) {
                    attr.code.push_back(static_cast<uint8_t>(inst.opcode));
                    const auto fieldIndex = cp.getFieldrefIndex(inst.className, inst.fieldName, inst.descriptor);
                    if (!fieldIndex) return fieldIndex.error();
                    util::push_back_be(attr.code, static_cast<uint16_t>(fieldIndex.value()));
                }
                else if constexpr (std::is_same_v<T, bytecode::InstructionMethodArg>) {
                    attr.code.push_back(static_cast<uint8_t>(inst.opcode));
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
