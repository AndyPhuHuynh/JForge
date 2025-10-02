#pragma once

#include <expected>
#include <iosfwd>

#include "jforge/constant_pool/constant_pool.hpp"
#include "jforge/classfile/method.hpp"

namespace jforge::classfile
{
    auto readMethodInfo(std::istream& stream, const constant_pool::ConstantPool& cp) -> std::expected<MethodInfo, std::string>;
}