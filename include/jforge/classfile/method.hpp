#pragma once

#include <cstdint>
#include <vector>

#include "jforge/attributes/attributes.hpp"

namespace jforge::classfile
{
    struct MethodInfo
    {
        uint16_t accessFlags;
        uint16_t nameIndex;
        uint16_t descriptorIndex;
        uint16_t attributeCounts;
        std::vector<attributes::AttributeInfo> attributes;
    };
}
