#pragma once

#include "iosfwd"

#include "jforge/attributes/attributes.hpp"

namespace jforge::attributes
{
    auto printCode(std::ostream& os, const Code& code, size_t indent) -> void;
    auto printLineNumberTable(std::ostream& os, const LineNumberTable& table, size_t indent) -> void;
    auto printAttribute(std::ostream& os, const AttributeInfo& attribute, size_t index) -> void;
}