#include "jforge/attributes/printer.hpp"

#include <iostream>

#include "jforge/classfile/printer.hpp"

auto jforge::classfile::printMethod(std::ostream& os, const MethodInfo& method) -> void
{
    os << "Access flags:     " << method.accessFlags << "\n";
    os << "Name index:       " << method.nameIndex << "\n";
    os << "Descriptor Index: " << method.descriptorIndex << "\n";
    os << "Attribute counts: " << method.attributeCounts << "\n";
    for (const auto& attr : method.attributes)
    {
        printAttribute(os, attr, 4);
    }
}
