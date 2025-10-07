#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include "jforge/constant_pool/tags.hpp"

namespace jforge::constant_pool
{
    struct NullInfo {};

    struct Utf8Info // 1
    {
        uint16_t length;
        std::string bytes{};
    };

    struct IntegerInfo // 3
    {
        int32_t value;
    };

    struct FloatInfo // 4
    {
        float value;
    };

    struct LongInfo // 5
    {
        int64_t value;
    };

    struct DoubleInfo // 6
    {
        double value;
    };

    struct ClassInfo // 7
    {
        uint16_t nameIndex;
    };

    struct ResolvedClassInfo
    {
        std::string_view name;
    };

    struct StringInfo // 8
    {
        uint16_t stringIndex;
    };

    struct FieldrefInfo // 9
    {
        uint16_t classIndex;
        uint16_t nameAndTypeIndex;
    };

    struct ResolvedFieldrefInfo
    {
        std::string_view className;
        std::string_view name;
        std::string_view type;
    };

    struct MethodrefInfo // 10
    {
        uint16_t classIndex;
        uint16_t nameAndTypeIndex;
    };

    struct ResolvedMethodrefInfo
    {
        std::string_view className;
        std::string_view name;
        std::string_view type;
    };

    struct InterfaceMethodrefInfo // 11
    {
        uint16_t classIndex;
        uint16_t nameAndTypeIndex;
    };

    struct ResolvedInterfaceMethodrefInfo
    {
        std::string_view className;
        std::string_view name;
        std::string_view type;
    };

    struct NameAndTypeInfo // 12
    {
        uint16_t nameIndex;
        uint16_t descriptorIndex;
    };

    struct ResolvedNameAndTypeInfo
    {
        std::string_view name;
        std::string_view type;
    };

    using PoolEntry = std::variant<
        NullInfo,
        Utf8Info,
        IntegerInfo,
        FloatInfo,
        LongInfo,
        DoubleInfo,
        ClassInfo,
        StringInfo,
        FieldrefInfo,
        MethodrefInfo,
        InterfaceMethodrefInfo,
        NameAndTypeInfo
    >;

    [[nodiscard]] constexpr auto tagFromEntry(const PoolEntry& entry) -> Tag
    {
        return std::visit([]<typename T>(const T&) -> Tag
        {
            if constexpr (std::is_same_v<T, NullInfo>)               return Tag::None;
            if constexpr (std::is_same_v<T, Utf8Info>)               return Tag::Utf8;
            if constexpr (std::is_same_v<T, ClassInfo>)              return Tag::Class;
            if constexpr (std::is_same_v<T, StringInfo>)             return Tag::String;
            if constexpr (std::is_same_v<T, FieldrefInfo>)           return Tag::Fieldref;
            if constexpr (std::is_same_v<T, MethodrefInfo>)          return Tag::Methodref;
            if constexpr (std::is_same_v<T, InterfaceMethodrefInfo>) return Tag::InterfaceMethodref;
            if constexpr (std::is_same_v<T, NameAndTypeInfo>)        return Tag::NameAndType;
            return Tag::None;
        }, entry);
    }

    template <typename EntryType>
    [[nodiscard]] constexpr auto tagFromType() -> Tag
    {
        if constexpr (std::is_same_v<EntryType, Utf8Info>)                    return Tag::Utf8;
        else if constexpr (std::is_same_v<EntryType, ClassInfo>)              return Tag::Class;
        else if constexpr (std::is_same_v<EntryType, StringInfo>)             return Tag::String;
        else if constexpr (std::is_same_v<EntryType, FieldrefInfo>)           return Tag::Fieldref;
        else if constexpr (std::is_same_v<EntryType, MethodrefInfo>)          return Tag::Methodref;
        else if constexpr (std::is_same_v<EntryType, InterfaceMethodrefInfo>) return Tag::InterfaceMethodref;
        else if constexpr (std::is_same_v<EntryType, NameAndTypeInfo>)        return Tag::NameAndType;
        else return Tag::None;
    }
}