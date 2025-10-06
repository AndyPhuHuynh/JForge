#pragma once

#include <iosfwd>

#include "jforge/constant_pool/constant_pool.hpp"
#include "jforge/constant_pool/infos.hpp"

namespace jforge::writer
{
    auto writeConstantPoolEntry(std::ostream& os, const constant_pool::PoolEntry& entry) -> void;
    auto writeConstantPool(std::ostream& os, const constant_pool::ConstantPool& cp) -> void;
}
