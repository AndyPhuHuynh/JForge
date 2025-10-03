#include "jforge/attributes/printer.hpp"

#include <iostream>

#include "jforge/util/printing.hpp"

auto jforge::attributes::printCode(std::ostream& os, const Code& code, const size_t indent) -> void
{
    os << util::Indent(indent) << "Max stack:   " << code.maxStack << "\n";
    os << util::Indent(indent) << "Max locals:  " << code.maxLocals << "\n";
    os << util::Indent(indent) << "Code length: " << code.codeLength << "\n";
    os << util::Indent(indent);
    os << std::hex << "0x";
    for (uint32_t i = 0; i < code.codeLength; i++)
    {
        os << +(code.code[i]) << " ";
    }
    os << std::dec << "\n";
    os << util::Indent(indent) << "Exception table length: " << code.exceptionTableLength << "\n";
    for (size_t i = 0; i < code.exceptionTableLength; i++)
    {
        const auto& [startPc, endPc, handlerPc, catchType] = code.exceptionTable[i];
        os << util::Indent(indent) << "Exception   " << i << ": ";
        os << util::Indent(indent) << "Start pc:   " << startPc;
        os << util::Indent(indent) << "End pc:     " << endPc;
        os << util::Indent(indent) << "Handler pc: " << handlerPc;
        os << util::Indent(indent) << "Catch type: " << catchType;
    }
    os << util::Indent(indent) << "Attribute count: " << code.attributesCount << "\n";
    for (const auto& attr : code.attributes)
    {
        printAttribute(os, attr, indent + 4);
    }
}

auto jforge::attributes::printSourceFile(std::ostream& os, const SourceFile& source, const size_t indent) -> void
{
    os << util::Indent(indent) << "Source file index: " << source.sourceFileIndex << "\n";
}

auto jforge::attributes::printLineNumberTable(std::ostream& os, const LineNumberTable& table, size_t indent) -> void
{
    os << util::Indent(indent) << "Length: " << table.length << "\n";
    indent += 4;
    for (size_t i = 0; i < table.length; i++)
    {
        os << util::Indent(indent) << "Start pc:    " << table.entries[i].startPc << "\n";
        os << util::Indent(indent) << "Line number: " << table.entries[i].lineNumber << "\n";
        os << "\n";
    }
}

auto jforge::attributes::printAttribute(std::ostream& os, const AttributeInfo& attribute, const size_t index) -> void
{
    std::visit([&os, index]<typename T>(const T& attr) {
        if constexpr (std::is_same_v<T, Code>)                 printCode(os, attr, index);
        else if constexpr (std::is_same_v<T, SourceFile>)      printSourceFile(os, attr, index);
        else if constexpr (std::is_same_v<T, LineNumberTable>) printLineNumberTable(os, attr, index);
        else
        {
            std::cerr << "Unsupported attribute for printing" << std::endl;
        }
    }, attribute.value);
}
