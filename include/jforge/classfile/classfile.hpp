#pragma once

#include <cstdint>

#include "jforge/classfile/method.hpp"
#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::classfile
{
    struct ClassFile
    {
        uint8_t magic[4]{};
        uint16_t minorVersion = 0;
        uint16_t majorVersion = 0;
        uint16_t constantPoolCount = 0;
        constant_pool::ConstantPool constantPool{};
        uint16_t accessFlags = 0;
        uint16_t thisClass = 0;
        uint16_t superClass = 0;
        uint16_t interfacesCount = 0;
        // Interfaces
        uint16_t fieldsCount = 0;
        // Fields
        uint16_t methodsCount = 0;
        std::vector<MethodInfo> methods;
        uint16_t attributesCount;
        std::vector<attributes::AttributeInfo> attributes;
    };
}