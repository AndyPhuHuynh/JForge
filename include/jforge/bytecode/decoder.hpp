#pragma once

#include <cstdint>
#include <span>

#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::bytecode
{
    auto printBytecodes(const constant_pool::ConstantPool& cp, std::span<const uint8_t> bytes) -> void;
}