#pragma once

#include <cstdint>
#include <string_view>

namespace jforge::constant_pool
{
    enum class Tag : uint8_t
    {
        None                = 0,
        Utf8                = 1,
        Integer             = 3,
        Float               = 4,
        Long                = 5,
        Double              = 6,
        Class               = 7,
        String              = 8,
        Fieldref            = 9,
        Methodref           = 10,
        InterfaceMethodref  = 11,
        NameAndType         = 12,
        MethodHandle        = 15,
        MethodType          = 16,
        Dynamic             = 17,
        InvokeDynamic       = 18,
        Module              = 19,
        Package             = 20
    };

    [[nodiscard]] constexpr auto tagToString(const Tag tag) -> std::string_view
    {
        switch (tag)
        {
            case Tag::Utf8:               return "Utf8";
            case Tag::Integer:            return "Integer";
            case Tag::Float:              return "Float";
            case Tag::Long:               return "Long";
            case Tag::Double:             return "Double";
            case Tag::Class:              return "Class";
            case Tag::String:             return "String";
            case Tag::Fieldref:           return "Fieldref";
            case Tag::Methodref:          return "Methodref";
            case Tag::InterfaceMethodref: return "InterfaceMethodref";
            case Tag::NameAndType:        return "NameAndType";
            case Tag::MethodHandle:       return "MethodHandle";
            case Tag::MethodType:         return "MethodType";
            case Tag::Dynamic:            return "Dynamic";
            case Tag::InvokeDynamic:      return "InvokeDynamic";
            case Tag::Module:             return "Module";
            case Tag::Package:            return "Package";
            default:                      return "None";
        }
    }

    [[nodiscard]] constexpr auto tagFromNum(const uint8_t num) -> Tag
    {
        switch (num)
        {
            case 1:  return Tag::Utf8;
            case 3:  return Tag::Integer;
            case 4:  return Tag::Float;
            case 5:  return Tag::Long;
            case 6:  return Tag::Double;
            case 7:  return Tag::Class;
            case 8:  return Tag::String;
            case 9:  return Tag::Fieldref;
            case 10: return Tag::Methodref;
            case 11: return Tag::InterfaceMethodref;
            case 12: return Tag::NameAndType;
            case 15: return Tag::MethodHandle;
            case 16: return Tag::MethodType;
            case 17: return Tag::Dynamic;
            case 18: return Tag::InvokeDynamic;
            case 19: return Tag::Module;
            case 20: return Tag::Package;
            default: return Tag::None;
        }
    }
}
