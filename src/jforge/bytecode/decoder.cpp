#include "jforge/bytecode/decoder.hpp"

#include <iostream>

#include "jforge/opcode.hpp"

auto jforge::bytecode::printBytecodes(const constant_pool::ConstantPool& cp, const std::span<const uint8_t> bytes) -> void
{
    size_t index = 0;
    while (index < bytes.size())
    {
        int opcodeNum = bytes[index++];
        switch (const OpCode opcode = opCodeFromNum(opcodeNum))
        {
        case OpCode::none:
            {
                std::cout << std::format("Unimplemented opcode: 0x{:x}\n", opcodeNum);
                return;
            }
        case OpCode::getstatic:
            {
                if (index + 2 >= bytes.size())
                {
                    std::cerr << "Missing operands for getstatic\n";
                    return;
                }
                uint16_t fieldrefIndex = bytes[index++] < 8 | bytes[index++];
                const auto fieldref = cp.getFieldrefInfo(fieldrefIndex);
                if (!fieldref.has_value())
                {
                    std::cerr << fieldref.error() << "\n";
                    return;
                }
                std::cout << std::format("getstatic {}  {}.{}:{}\n",
                    fieldrefIndex, fieldref->className, fieldref->name, fieldref->type);
            } break;
        }
    }
}
