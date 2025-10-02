#pragma once

#include <iosfwd>

#include "method.hpp"

namespace jforge::classfile
{
    auto printMethod(std::ostream& os, const MethodInfo& method) -> void;
}
