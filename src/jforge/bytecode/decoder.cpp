#include "jforge/bytecode/decoder.hpp"

#include <iostream>

#include "jforge/opcode.hpp"
#include "jforge/util/file.hpp"
#include "jforge/util/span.hpp"

auto jforge::bytecode::printBytecodes(const constant_pool::ConstantPool& cp, const std::span<const uint8_t> bytes) -> void
{
    util::SpanReader span{bytes};
    while (span.position() < bytes.size())
    {
        size_t opcodeIndex = span.position();
        const auto opcodeNum = span.read_bytes_be<uint8_t>();
        switch (const OpCode opcode =  opCodeFromNum(opcodeNum))
        {
        case OpCode::none:
            {
                std::cout << std::format("Unimplemented opcode: 0x{:x}\n", opcodeNum);
                return;
            }
        case OpCode::aconst_null: // 0x01
        case OpCode::iconst_m1: // 0x02
        case OpCode::iconst_0: // 0x03
        case OpCode::iconst_1: // 0x04
        case OpCode::iconst_2: // 0x05
        case OpCode::iconst_3: // 0x06
        case OpCode::iconst_4: // 0x07
        case OpCode::iconst_5: // 0x08
        case OpCode::lconst_0: // 0x09
        case OpCode::lconst_1: // 0x0a
        case OpCode::fconst_0: // 0x0b
        case OpCode::fconst_1: // 0x0c
        case OpCode::fconst_2: // 0x0d
        case OpCode::dconst_0: // 0x0e
        case OpCode::dconst_1: // 0x0f
            {
                std::cout << std::format("{}: {}\n", opcodeIndex, opCodeToString(opcode));
            } break;
        case OpCode::bipush: // 0x10
            {
                if (!span.can_read(1)) {
                    std::cerr << "Missing operand for bipush" << std::endl;
                    return;
                }
                int8_t value = span.read_bytes_be<int8_t>();
                std::cout << std::format("{}: {: <14} #{: <5} // String {}\n", opcodeIndex, opCodeToString(opcode), value);
            } break;
        case OpCode::sipush: // 0x11
            {
                if (!span.can_read(2)) {
                    std::cerr << "Missing operand for sipush" << std::endl;
                    return;
                }
                int16_t value = span.read_bytes_be<int16_t>();
                std::cout << std::format("{}: {: <14} #{: <5} // String {}\n", opcodeIndex, opCodeToString(opcode), value);
            } break;
        case OpCode::ldc: // 0x12
            {
                if (!span.can_read(1)) {
                    std::cerr << "Missing operand for ldc" << std::endl;
                    return;
                }
                const auto poolIndex = span.read_bytes_be<uint8_t>();
                if (const auto intValue = cp.getInt(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // Int {}\n",
                        opcodeIndex, "ldc", poolIndex, *intValue);
                }
                else if (const auto floatValue = cp.getFloat(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // Float {}\n",
                        opcodeIndex, "ldc", poolIndex, *floatValue);
                }
                else if (const auto classInfo = cp.getClassInfo(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // Class {}\n",
                        opcodeIndex, "ldc_w", poolIndex, classInfo->name);
                }
                else if (const auto string = cp.getStringInfo(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // String {}\n",
                        opcodeIndex, "ldc", poolIndex, *string);
                }
                else {
                    std::cerr << "Unable to load ldc at index " << poolIndex << std::endl;
                    return;
                }
            } break;
        case OpCode::ldc_w: // 0x13
            {
                if (!span.can_read(2)) {
                    std::cerr << "Missing operands for ldc_w" << std::endl;
                    return;
                }
                const auto poolIndex = span.read_bytes_be<uint16_t>();
                if (const auto intValue = cp.getInt(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // Int {}\n",
                        opcodeIndex, "ldc_w", poolIndex, *intValue);
                }
                else if (const auto floatValue = cp.getFloat(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // Float {}\n",
                        opcodeIndex, "ldc_w", poolIndex, *floatValue);
                }
                else if (const auto classInfo = cp.getClassInfo(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // Class {}\n",
                        opcodeIndex, "ldc_w", poolIndex, classInfo->name);
                }
                else if (const auto string = cp.getStringInfo(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // String {}\n",
                        opcodeIndex, "ldc_w", poolIndex, *string);
                }
                else {
                    std::cerr << "Unable to load ldc_w at index " << poolIndex << std::endl;
                    return;
                }
            } break;
        case OpCode::ldc2_w: // 0x14
            {
                if (!span.can_read(2)) {
                    std::cerr << "Missing operands for ldc2_w" << std::endl;
                    return;
                }
                const auto poolIndex = span.read_bytes_be<uint16_t>();
                if (const auto longValue = cp.getLong(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // Long {}\n",
                        opcodeIndex, "ldc_w", poolIndex, *longValue);
                }
                else if (const auto doubleValue = cp.getDouble(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // Double {}\n",
                        opcodeIndex, "ldc_w", poolIndex, *doubleValue);
                }
            } break;
        case OpCode::iload_0:  // 0x1a
        case OpCode::iload_1:  // 0x1b
        case OpCode::iload_2:  // 0x1c
        case OpCode::iload_3:  // 0x1d
        case OpCode::aload_0:  // 0x2a
        case OpCode::aload_1:  // 0x2b
        case OpCode::aload_2:  // 0x2c
        case OpCode::aload_3:  // 0x2d
        case OpCode::istore_0: // 0x3b
        case OpCode::istore_1: // 0x3c
        case OpCode::istore_2: // 0x3d
        case OpCode::istore_3: // 0x3e
        case OpCode::iadd:     // 0x60
        case OpCode::isub:     // 0x64
        case OpCode::imul:     // 0x68
        case OpCode::idiv:     // 0x6c
        case OpCode::irem:     // 0x70
        case OpCode::ret:      // 0xb1
            {
                std::cout << std::format("{}: {}\n", opcodeIndex, opCodeToString(opcode));
            } break;
        case OpCode::getstatic: // 0xb2
            {
                if (!span.can_read(2))
                {
                    std::cerr << "Missing operands for getstatic\n";
                    return;
                }
                const auto fieldrefIndex = span.read_bytes_be<uint16_t>();
                const auto fieldref = cp.getFieldrefInfo(fieldrefIndex);
                if (!fieldref.has_value())
                {
                    std::cerr << fieldref.error() << "\n";
                    return;
                }
                std::cout << std::format("{}: {: <14} #{: <5} // Field {}.{}:{}\n",
                    opcodeIndex, "getstatic", fieldrefIndex, fieldref->className, fieldref->name, fieldref->type);
            } break;
        case OpCode::invokevirtual: // 0xb6
            {
                if (!span.can_read(2))
                {
                    std::cerr << "Missing operands for invokevirtual\n";
                    return;
                }
                const auto methodrefIndex = span.read_bytes_be<uint16_t>();
                const auto methodref = cp.getMethodrefInfo(methodrefIndex);
                if (!methodref.has_value())
                {
                    std::cerr << methodref.error() << "\n";
                    return;
                }
                std::cout << std::format("{}: {: <14} #{: <5} // Method {}.{}:{}\n",
                    opcodeIndex, "invokevirtual", methodrefIndex, methodref->className, methodref->name, methodref->type);
            } break;
        case OpCode::invokespecial: // 0xb7
            {
                if (!span.can_read(2))
                {
                    std::cerr << "Missing operands for invokespecial\n";
                    return;
                }
                const auto methodrefIndex = span.read_bytes_be<uint16_t>();
                const auto methodref = cp.getMethodrefInfo(methodrefIndex);
                if (!methodref.has_value())
                {
                    std::cerr << methodref.error() << "\n";
                    return;
                }
                std::cout << std::format("{}: {: <14} #{: <5} // Method {}.{}:{}\n",
                    opcodeIndex, "invokespecial", methodrefIndex, methodref->className, methodref->name, methodref->type);
            } break;
        case OpCode::invokestatic: // 0xb8
            {
                if (!span.can_read(2))
                {
                    std::cerr << "Missing operands for invokestatic\n";
                    return;
                }
                const auto methodrefIndex = span.read_bytes_be<uint16_t>();
                const auto methodref = cp.getMethodrefInfo(methodrefIndex);
                if (!methodref.has_value())
                {
                    std::cerr << methodref.error() << "\n";
                    return;
                }
                std::cout << std::format("{}: {: <14} #{: <5} // Method {}.{}:{}\n",
                    opcodeIndex, "invokestatic", methodrefIndex, methodref->className, methodref->name, methodref->type);
            } break;
        }
    }
}
