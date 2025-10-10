#pragma once

#include <iosfwd>

#include "jforge/classfile/method.hpp"
#include "jforge/classfile/classfile.hpp"

namespace jforge::writer
{
    auto writeMethod(std::ostream& os, const classfile::MethodInfo& method) -> void;
    auto writeClassFile(std::ostream& os, const classfile::ClassFile& classFile) -> void;
}