#pragma once

#include <expected>
#include <istream>

#include "jforge/constant_pool/constant_pool.hpp"
#include "jforge/constant_pool/infos.hpp"

namespace jforge::constant_pool
{
    auto readPoolEntry(std::istream& stream) -> std::expected<PoolEntry, std::string>;
    auto readConstantPool(std::istream& stream, uint16_t count) -> std::expected<ConstantPool, std::string>;
}