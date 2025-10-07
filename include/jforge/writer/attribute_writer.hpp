#pragma once

#include <iosfwd>

#include "jforge/attributes/attributes.hpp"

namespace jforge::writer
{
    auto writeCodeAttribute(std::ostream& os, const attributes::Code& attr) -> void;
    auto writeAttribute(std::ostream& os, const attributes::AttributeInfo& attr) -> void;
}