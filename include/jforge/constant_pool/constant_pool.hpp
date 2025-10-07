#pragma once

#include <expected>
#include <format>
#include <functional>
#include <ranges>
#include <unordered_map>
#include <vector>

#include "jforge/constant_pool/infos.hpp"

namespace jforge::constant_pool
{
    class ConstantPool
    {
        using Hash  = uint64_t;
        using Index = uint16_t;
        std::unordered_map<Hash, Index> m_utf8Entries;
        std::unordered_map<int32_t, Index> m_intEntries;
        std::unordered_map<float, Index> m_floatEntries;
        std::unordered_map<int64_t, Index> m_longEntries;
        std::unordered_map<double, Index> m_doubleEntries;
        std::unordered_map<Hash, Index> m_classEntries;
        std::unordered_map<Hash, Index> m_stringEntries;
        std::unordered_map<Hash, Index> m_fieldrefEntries;
        std::unordered_map<Hash, Index> m_methodrefEntries;
        std::unordered_map<Hash, Index> m_interfaceMethodrefEntries;
        std::unordered_map<Hash, Index> m_nameAndTypeEntries;
        std::vector<PoolEntry> m_entries;

    public:
        ConstantPool();

        [[nodiscard]] auto size() const -> size_t;
        [[nodiscard]] auto allEntries() const -> const std::vector<PoolEntry>&;
        [[nodiscard]] auto realEntries() const {
            return m_entries | std::views::filter([](const PoolEntry& e) { return !std::holds_alternative<NullInfo>(e); });
        }

        [[nodiscard]] auto operator[](size_t index) const -> const PoolEntry&;
        [[nodiscard]] auto get(size_t index) const -> std::expected<std::reference_wrapper<const PoolEntry>, std::string>;

        auto addEntry(PoolEntry entry) -> PoolEntry&;
        [[nodiscard]] auto getUtf8(size_t index) const -> std::expected<std::string_view, std::string>;
        [[nodiscard]] auto getInt(size_t index) const -> std::expected<int32_t, std::string>;
        [[nodiscard]] auto getFloat(size_t index) const -> std::expected<float, std::string>;
        [[nodiscard]] auto getLong(size_t index) const -> std::expected<int64_t, std::string>;
        [[nodiscard]] auto getDouble(size_t index) const -> std::expected<double, std::string>;
        [[nodiscard]] auto getClassInfo(size_t index) const -> std::expected<ResolvedClassInfo, std::string>;
        [[nodiscard]] auto resolveStringInfo(const StringInfo& info) const -> std::expected<std::string_view, std::string>;
        [[nodiscard]] auto getStringInfo(size_t index) const -> std::expected<std::string_view, std::string>;
        [[nodiscard]] auto getFieldrefInfo(size_t index) const -> std::expected<ResolvedFieldrefInfo, std::string>;
        [[nodiscard]] auto getMethodrefInfo(size_t index) const -> std::expected<ResolvedMethodrefInfo, std::string>;
        [[nodiscard]] auto getInterfaceMethodrefInfo(size_t index) const -> std::expected<ResolvedInterfaceMethodrefInfo, std::string>;
        [[nodiscard]] auto getNameAndTypeInfo(size_t index) const -> std::expected<ResolvedNameAndTypeInfo, std::string>;

        auto addUtf8(std::string_view value) -> uint16_t;
        auto addInt(int32_t value) -> uint16_t;
        auto addFloat(float value) -> uint16_t;
        auto addLong(int64_t value) -> uint16_t;
        auto addDouble(double value) -> uint16_t;
        auto addClass(std::string_view className) -> uint16_t;
        auto addString(std::string_view value) -> uint16_t;
        auto addFieldref(std::string_view className, std::string_view fieldName, std::string_view descriptor) -> uint16_t;
        auto addMethodref(std::string_view className, std::string_view methodName, std::string_view descriptor) -> uint16_t;
        auto addInterfaceMethodref(std::string_view className, std::string_view interfaceMethodName, std::string_view descriptor) -> uint16_t;
        auto addNameAndType(std::string_view name, std::string_view type) -> uint16_t;

        [[nodiscard]] auto getUtf8Index(std::string_view value) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getIntIndex(int32_t value) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getFloatIndex(float value) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getLongIndex(int64_t value) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getDoubleIndex(double value) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getClassIndex(std::string_view className) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getStringIndex(std::string_view value) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getFieldrefIndex(std::string_view className, std::string_view fieldName, std::string_view descriptor) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getMethodrefIndex(std::string_view className, std::string_view methodName, std::string_view descriptor) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getInterfaceMethodrefIndex(std::string_view className, std::string_view interfaceMethodName, std::string_view descriptor) const -> std::expected<uint16_t, std::string>;
        [[nodiscard]] auto getNameAndTypeIndex(std::string_view name, std::string_view type) const -> std::expected<uint16_t, std::string>;
    };
}