#include "jforge/bytecode/decoder.hpp"

#include <algorithm>
#include <iostream>

#include "jforge/opcode.hpp"
#include "jforge/util/file.hpp"
#include "jforge/util/span.hpp"

static bool canRead(const std::span<const uint8_t> bytes, const size_t index, const size_t count) {
    return index + count <= bytes.size();
}

auto jforge::bytecode::printBytecodes(const constant_pool::ConstantPool& cp, const std::span<const uint8_t> bytes) -> void
{
    util::SpanReader span{bytes};
    while (span.position() < bytes.size())
    {
        size_t opcodeIndex = span.position();
        switch (const auto opcodeNum = span.read_bytes_be<uint8_t>(); opCodeFromNum(opcodeNum))
        {
        case OpCode::none:
            {
                std::cout << std::format("Unimplemented opcode: 0x{:x}\n", opcodeNum);
                return;
            }
        case OpCode::ldc: // 0x12
            {
                if (!span.can_read(1))
                {
                    std::cerr << "Missing operands for ldc" << std::endl;
                    return;
                }
                const auto poolIndex = span.read_bytes_be<uint8_t>();
                // TODO: Support other constant pool entries here
                const auto poolEntry = cp.get(poolIndex);
                if (!poolEntry)
                {
                    std::cerr << poolEntry.error() << std::endl;
                    return;
                }
                if (std::holds_alternative<constant_pool::StringInfo>(poolEntry->get()))
                {
                    const auto string = cp.resolveStringInfo(std::get<constant_pool::StringInfo>(poolEntry->get()));
                    if (!string.has_value())
                    {
                        std::cerr << string.error() << std::endl;
                        return;
                    }
                    std::cout << std::format("{}: {: <14} #{: <5} // {}\n",
                        opcodeIndex, "ldc", poolIndex, *string);
                }
                else
                {
                    std::cerr << "Unsupported type for ldc" << std::endl;
                    return;
                }
            } break;
        case OpCode::ret: // 0xb1
            {
                std::cout << std::format("{}: ret\n", opcodeIndex);
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
                std::cout << std::format("{}: {: <14} #{: <5} // {}.{}:{}\n",
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
                std::cout << std::format("{}: {: <14} #{: <5} // {}.{}:{}\n",
                    opcodeIndex, "invokevirtual", methodrefIndex, methodref->className, methodref->name, methodref->type);
            } break;
        }
    }
}
