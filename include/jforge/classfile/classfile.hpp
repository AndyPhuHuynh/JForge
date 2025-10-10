#pragma once

#include <cstdint>

#include "jforge/classfile/method.hpp"
#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::classfile
{
    struct ClassFile
    {
        uint16_t minorVersion = 0;
        uint16_t majorVersion = 0;
        constant_pool::ConstantPool constantPool{};
        uint16_t accessFlags = 0;
        uint16_t thisClass = 0;
        uint16_t superClass = 0;
        // Interfaces
        // Fields
        std::vector<MethodInfo> methods;
        std::vector<attributes::AttributeInfo> attributes;
    };
}