#pragma once

#include <cstdint>
#include <variant>
#include <vector>

namespace jforge::attributes
{
    struct AttributeInfo;

    struct ExceptionTableEntry
    {
        uint16_t startPc;
        uint16_t endPc;
        uint16_t handlerPc;
        uint16_t catchType;
    };

    struct Code
    {
        uint16_t maxStack;
        uint16_t maxLocals;
        uint32_t codeLength;
        std::vector<uint8_t> code;
        uint16_t exceptionTableLength;
        std::vector<ExceptionTableEntry> exceptionTable;
        uint16_t attributesCount;
        std::vector<AttributeInfo> attributes;
    };

    struct LineNumberTableEntry
    {
        uint16_t startPc;
        uint16_t lineNumber;
    };

    struct LineNumberTable
    {
        uint16_t length;
        std::vector<LineNumberTableEntry> entries;
    };

    using AttributeVariant = std::variant<
        Code,
        LineNumberTable
    >;

    struct AttributeInfo
    {
        uint16_t nameIndex;
        uint32_t length;
        AttributeVariant value;
    };
}