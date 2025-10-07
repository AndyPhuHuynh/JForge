#pragma once

#include <iosfwd>

#include "jforge/classfile/method.hpp"

namespace jforge::writer
{
    auto writeMethod(std::ostream& os, const classfile::MethodInfo& method) -> void;
}