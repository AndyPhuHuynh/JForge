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

    struct Code // Section 4.7.3
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

    struct SourceFile // section 4.7.10
    {
        uint16_t sourceFileIndex;
    };

    struct LineNumberTableEntry
    {
        uint16_t startPc;
        uint16_t lineNumber;
    };

    struct LineNumberTable // Section 4.7.13
    {
        uint16_t length;
        std::vector<LineNumberTableEntry> entries;
    };

    using AttributeVariant = std::variant<
        Code,
        SourceFile,
        LineNumberTable
    >;

    struct AttributeInfo
    {
        uint16_t nameIndex;
        uint32_t length;
        AttributeVariant value;
    };
}