#include "jforge/bytecode/decoder.hpp"

#include <iostream>

#include "../../../include/jforge/bytecode/opcode.hpp"
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
                auto value = span.read_bytes_be<int8_t>();
                std::cout << std::format("{}: {: <14} {}\n", opcodeIndex, opCodeToString(opcode), value);
            } break;
        case OpCode::sipush: // 0x11
            {
                if (!span.can_read(2)) {
                    std::cerr << "Missing operand for sipush" << std::endl;
                    return;
                }
                auto value = span.read_bytes_be<int16_t>();
                std::cout << std::format("{}: {: <14} {}\n", opcodeIndex, opCodeToString(opcode), value);
            } break;
        case OpCode::ldc: // 0x12
            {
                if (!span.can_read(1)) {
                    std::cerr << "Missing operand for ldc" << std::endl;
                    return;
                }
                const auto poolIndex = span.read_bytes_be<uint8_t>();
                if (const auto intValue = cp.getInt(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // int {}\n",
                        opcodeIndex, "ldc", poolIndex, *intValue);
                }
                else if (const auto floatValue = cp.getFloat(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // float {}\n",
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
                    std::cout << std::format("{}: {: <14} #{: <5} // int {}\n",
                        opcodeIndex, "ldc_w", poolIndex, *intValue);
                }
                else if (const auto floatValue = cp.getFloat(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // float {}\n",
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
                    std::cout << std::format("{}: {: <14} #{: <5} // long {}\n",
                        opcodeIndex, "ldc_w", poolIndex, *longValue);
                }
                else if (const auto doubleValue = cp.getDouble(poolIndex)) {
                    std::cout << std::format("{}: {: <14} #{: <5} // double {}\n",
                        opcodeIndex, "ldc_w", poolIndex, *doubleValue);
                }
            } break;
        case OpCode::iload: // 0x15
        case OpCode::lload: // 0x16
        case OpCode::fload: // 0x17
        case OpCode::dload: // 0x18
        case OpCode::aload: // 0x19
            {
                if (!span.can_read(1)) {
                    std::cerr << "Missing operands for " << opCodeToString(opcode) << std::endl;
                }
                const auto index = span.read_bytes_be<uint8_t>();
                std::cout << std::format("{}: {: <14} {}\n", opcodeIndex, opCodeToString(opcode), index);
            } break;
        case OpCode::iload_0:  // 0x1a
        case OpCode::iload_1:  // 0x1b
        case OpCode::iload_2:  // 0x1c
        case OpCode::iload_3:  // 0x1d

        case OpCode::lload_0:  // 0x1e
        case OpCode::lload_1:  // 0x1f
        case OpCode::lload_2:  // 0x20
        case OpCode::lload_3:  // 0x21

        case OpCode::fload_0:  // 0x22
        case OpCode::fload_1:  // 0x23
        case OpCode::fload_2:  // 0x24
        case OpCode::fload_3:  // 0x25

        case OpCode::dload_0:  // 0x26
        case OpCode::dload_1:  // 0x27
        case OpCode::dload_2:  // 0x28
        case OpCode::dload_3:  // 0x29

        case OpCode::aload_0:  // 0x2a
        case OpCode::aload_1:  // 0x2b
        case OpCode::aload_2:  // 0x2c
        case OpCode::aload_3:  // 0x2d

        case OpCode::iaload: // 0x2e
        case OpCode::laload: // 0x2f
        case OpCode::faload: // 0x30
        case OpCode::daload: // 0x31
        case OpCode::aaload: // 0x32
        case OpCode::baload: // 0x33
        case OpCode::caload: // 0x34
        case OpCode::saload: // 0x35
            {
                std::cout << std::format("{}: {}\n", opcodeIndex, opCodeToString(opcode));
            } break;
        case OpCode::istore: // 0x36
        case OpCode::lstore: // 0x37
        case OpCode::fstore: // 0x38
        case OpCode::dstore: // 0x39
        case OpCode::astore: // 0x3a
            {
                if (!span.can_read(1)) {
                    std::cerr << "Missing operand for " << opCodeToString(opcode) << std::endl;
                    return;
                }
                auto value = span.read_bytes_be<int8_t>();
                std::cout << std::format("{}: {: <14} #{: <5}\n", opcodeIndex, opCodeToString(opcode), value);
            } break;
        case OpCode::istore_0: // 0x3b
        case OpCode::istore_1: // 0x3c
        case OpCode::istore_2: // 0x3d
        case OpCode::istore_3: // 0x3e

        case OpCode::lstore_0: // 0x3f
        case OpCode::lstore_1: // 0x40
        case OpCode::lstore_2: // 0x41
        case OpCode::lstore_3: // 0x42

        case OpCode::fstore_0: // 0x43
        case OpCode::fstore_1: // 0x44
        case OpCode::fstore_2: // 0x45
        case OpCode::fstore_3: // 0x46

        case OpCode::dstore_0: // 0x47
        case OpCode::dstore_1: // 0x48
        case OpCode::dstore_2: // 0x49
        case OpCode::dstore_3: // 0x4a

        case OpCode::astore_0: // 0x4b
        case OpCode::astore_1: // 0x4c
        case OpCode::astore_2: // 0x4d
        case OpCode::astore_3: // 0x4e

        case OpCode::iastore:  // 0x4f
        case OpCode::lastore:  // 0x50
        case OpCode::fastore:  // 0x51
        case OpCode::dastore:  // 0x52
        case OpCode::aastore:  // 0x53
        case OpCode::bastore:  // 0x54
        case OpCode::castore:  // 0x55
        case OpCode::sastore:  // 0x56

        case OpCode::pop:      // 0x57
        case OpCode::pop2:     // 0x58
        case OpCode::dup:      // 0x59
        case OpCode::dup_x1:   // 0x5a
        case OpCode::dup_x2:   // 0x5b
        case OpCode::dup2:     // 0x5c
        case OpCode::dup2_x1:  // 0x5d
        case OpCode::dup2_x2:  // 0x5e
        case OpCode::swap:     // 0x5f

        case OpCode::iadd:     // 0x60
        case OpCode::ladd:     // 0x61
        case OpCode::fadd:     // 0x62
        case OpCode::dadd:     // 0x63

        case OpCode::isub:     // 0x64
        case OpCode::lsub:     // 0x65
        case OpCode::fsub:     // 0x66
        case OpCode::dsub:     // 0x67

        case OpCode::imul:     // 0x68
        case OpCode::lmul:     // 0x69
        case OpCode::fmul:     // 0x6a
        case OpCode::dmul:     // 0x6b

        case OpCode::idiv:     // 0x6c
        case OpCode::ldiv:     // 0x6d
        case OpCode::fdiv:     // 0x6e
        case OpCode::ddiv:     // 0x6f

        case OpCode::irem:     // 0x70
        case OpCode::lrem:     // 0x71
        case OpCode::frem:     // 0x72
        case OpCode::drem:     // 0x73

        case OpCode::ineg:     // 0x74
        case OpCode::lneg:     // 0x75
        case OpCode::fneg:     // 0x76
        case OpCode::dneg:     // 0x77

        case OpCode::ishl:     // 0x78
        case OpCode::lshl:     // 0x79
        case OpCode::ishr:     // 0x7a
        case OpCode::lshr:     // 0x7b
        case OpCode::iushr:    // 0x7c
        case OpCode::lushr:    // 0x7d

        case OpCode::iand:     // 0x7e
        case OpCode::land:     // 0x7f
        case OpCode::ior:      // 0x80
        case OpCode::lor:      // 0x81
        case OpCode::ixor:     // 0x82
        case OpCode::lxor:     // 0x83
            {
                std::cout << std::format("{}: {}\n", opcodeIndex, opCodeToString(opcode));
            } break;
        case OpCode::iinc:     // 0x84
            {
                if (!span.can_read(2)) {
                    std::cerr << "Missing operands for invokevirtual\n";
                    return;
                }
                const auto index = span.read_bytes_be<uint8_t>();
                const auto increment = span.read_bytes_be<uint8_t>();
                std::cout << std::format("{}: {: <14} {} {}\n", opcodeIndex, opCodeToString(opcode), index, increment);
            } break;
        case OpCode::i2l:      // 0x85
        case OpCode::i2f:      // 0x86
        case OpCode::i2d:      // 0x87
        case OpCode::l2i:      // 0x88
        case OpCode::l2f:      // 0x89
        case OpCode::l2d:      // 0x8a
        case OpCode::f2i:      // 0x8b
        case OpCode::f2l:      // 0x8c
        case OpCode::f2d:      // 0x8d
        case OpCode::d2i:      // 0x8e
        case OpCode::d2l:      // 0x8f
        case OpCode::d2f:      // 0x90
        case OpCode::i2b:      // 0x91
        case OpCode::i2c:      // 0x92
        case OpCode::i2s:      // 0x93
        case OpCode::lcmp:     // 0x94
        case OpCode::fcmpl:    // 0x95
        case OpCode::fcmpg:    // 0x96
        case OpCode::dcmpl:    // 0x97
        case OpCode::dcmpg:    // 0x98
            {
                std::cout << std::format("{}: {}\n", opcodeIndex, opCodeToString(opcode));
            } break;
        case OpCode::goto_:    // 0xa7
            {
                const auto label = span.read_bytes_be<uint16_t>();
                std::cout << std::format("{}: {: <14} {}\n", opcodeIndex, opCodeToString(opcode), label);
            } break;
        case OpCode::ret:      // 0xb1
            {
                std::cout << std::format("{}: {}\n", opcodeIndex, opCodeToString(opcode));
            } break;
        case OpCode::getstatic: // 0xb2
            {
                if (!span.can_read(2)) {
                    std::cerr << "Missing operands for getstatic\n";
                    return;
                }
                const auto fieldrefIndex = span.read_bytes_be<uint16_t>();
                const auto fieldref = cp.getFieldrefInfo(fieldrefIndex);
                if (!fieldref.has_value()) {
                    std::cerr << fieldref.error() << "\n";
                    return;
                }
                std::cout << std::format("{}: {: <14} #{: <5} // Field {}.{}:{}\n",
                    opcodeIndex, "getstatic", fieldrefIndex, fieldref->className, fieldref->name, fieldref->type);
            } break;
        case OpCode::invokevirtual: // 0xb6
            {
                if (!span.can_read(2)) {
                    std::cerr << "Missing operands for invokevirtual\n";
                    return;
                }
                const auto methodrefIndex = span.read_bytes_be<uint16_t>();
                const auto methodref = cp.getMethodrefInfo(methodrefIndex);
                if (!methodref.has_value()) {
                    std::cerr << methodref.error() << "\n";
                    return;
                }
                std::cout << std::format("{}: {: <14} #{: <5} // Method {}.{}:{}\n",
                    opcodeIndex, "invokevirtual", methodrefIndex, methodref->className, methodref->name, methodref->type);
            } break;
        case OpCode::invokespecial: // 0xb7
            {
                if (!span.can_read(2)) {
                    std::cerr << "Missing operands for invokespecial\n";
                    return;
                }
                const auto methodrefIndex = span.read_bytes_be<uint16_t>();
                const auto methodref = cp.getMethodrefInfo(methodrefIndex);
                if (!methodref.has_value()) {
                    std::cerr << methodref.error() << "\n";
                    return;
                }
                std::cout << std::format("{}: {: <14} #{: <5} // Method {}.{}:{}\n",
                    opcodeIndex, "invokespecial", methodrefIndex, methodref->className, methodref->name, methodref->type);
            } break;
        case OpCode::invokestatic: // 0xb8
            {
                if (!span.can_read(2)) {
                    std::cerr << "Missing operands for invokestatic\n";
                    return;
                }
                const auto methodrefIndex = span.read_bytes_be<uint16_t>();
                const auto methodref = cp.getMethodrefInfo(methodrefIndex);
                if (!methodref.has_value()) {
                    std::cerr << methodref.error() << "\n";
                    return;
                }
                std::cout << std::format("{}: {: <14} #{: <5} // Method {}.{}:{}\n",
                    opcodeIndex, "invokestatic", methodrefIndex, methodref->className, methodref->name, methodref->type);
            } break;
        case OpCode::goto_w:      // 0xc8
            {
                const auto label = span.read_bytes_be<uint32_t>();
                std::cout << std::format("{}: {: <14} {}\n", opcodeIndex, opCodeToString(opcode), label);
            } break;
        }
    }
}
