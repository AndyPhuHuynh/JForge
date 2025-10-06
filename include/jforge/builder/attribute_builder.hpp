#pragma once

#include <expected>
#include <vector>

#include "jforge/attributes/attributes.hpp"
#include "jforge/constant_pool/constant_pool.hpp"
#include "jforge/instructions.hpp"

namespace jforge::builder
{
    auto generateCodeAttribute(
        const constant_pool::ConstantPool& cp,
        const std::vector<Instructions>& instructions) -> std::expected<attributes::Code, std::string>;
}
