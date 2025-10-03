#pragma once

#include <expected>
#include <iosfwd>
#include <string>


#include "jforge/attributes/attributes.hpp"
#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::attributes
{
    auto readCode(std::istream& stream, const constant_pool::ConstantPool& cp) -> std::expected<Code, std::string>;
    auto readSourceFile(std::istream& stream) -> SourceFile;
    auto readLineNumberTable(std::istream& stream) -> LineNumberTable;
    auto readAttribute(std::istream& stream, const constant_pool::ConstantPool& cp) -> std::expected<AttributeInfo, std::string>;
}