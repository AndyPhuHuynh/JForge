#pragma once

#include <string>
#include <variant>

#include "jforge/bytecode/opcode.hpp"

namespace jforge::bytecode
{

    struct InstructionNoArg { OpCode opcode; };

    struct InstructionOneArgInt8
    {
        OpCode opcode;
        int8_t value;
    };

    struct InstructionOneArgUInt8
    {
        OpCode opcode;
        uint8_t value;
    };

    struct InstructionOneArgInt16
    {
        OpCode opcode;
        int16_t value;
    };

    struct InstructionLdcInt    { int32_t     value; };
    struct InstructionLdcFloat  { float       value; };
    struct InstructionLdcLong   { int64_t     value; };
    struct InstructionLdcDouble { double      value; };
    struct InstructionLdcString { std::string value; };
    struct InstructionLdcClass  { std::string className; };

    struct InstructionIINC
    {
        uint8_t index;
        uint8_t increment;
    };

    struct InstructionFieldArg
    {
        OpCode opcode;
        std::string className;
        std::string fieldName;
        std::string descriptor;
    };

    struct InstructionMethodArg
    {
        OpCode opcode;
        std::string className;
        std::string methodName;
        std::string descriptor;
    };

    using Instructions = std::variant<
        InstructionNoArg,
        InstructionOneArgInt8,
        InstructionOneArgUInt8,
        InstructionOneArgInt16,
        InstructionLdcInt,
        InstructionLdcFloat,
        InstructionLdcLong,
        InstructionLdcDouble,
        InstructionLdcClass,
        InstructionLdcString,
        InstructionIINC,
        InstructionFieldArg,
        InstructionMethodArg
    >;
}
