#pragma once

#include <cstdint>

#include "jforge/attributes/attributes.hpp"

namespace jforge::attributes
{
    auto calculateCodeLength(const Code& code) -> uint32_t;
}