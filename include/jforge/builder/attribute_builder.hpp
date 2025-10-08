#pragma once

#include <expected>
#include <vector>

#include "jforge/attributes/attributes.hpp"
#include "jforge/bytecode/instructions.hpp"
#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::builder
{
    auto generateCodeAttribute(
        const constant_pool::ConstantPool& cp,
        const std::vector<bytecode::Instructions>& instructions) -> std::expected<attributes::Code, std::string>;
}
