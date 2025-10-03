#pragma once

#include <expected>
#include <iosfwd>
#include <string>

#include "jforge/classfile/classfile.hpp"
#include "jforge/classfile/method.hpp"
#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::classfile
{
    auto readMethodInfo(std::istream& stream, const constant_pool::ConstantPool& cp) -> std::expected<MethodInfo, std::string>;
    auto readClassFile(std::istream& stream) -> std::expected<ClassFile, std::string>;
}