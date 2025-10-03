#pragma once

#include <expected>
#include <format>
#include <functional>
#include <optional>
#include <ranges>
#include <vector>

#include "jforge/constant_pool/infos.hpp"

namespace jforge::constant_pool
{
    class ConstantPool
    {
    private:
        std::vector<PoolEntry> m_entries;

        [[nodiscard]] static constexpr auto generateUnexpectedTypeMessage(std::string_view entryType, const size_t index) -> std::string
        {
            return std::format("Attempted to get {} info at index {}. Entry is not a {} info", entryType, index, entryType);
        }

        [[nodiscard]] static constexpr auto generateUnableToGetMessage(std::string_view name, const size_t index, std::string_view nestedError) -> std::string
        {
            return std::format("Unable to get {} at index {}. {}", name, index, nestedError);
        }
;    public:
        constexpr ConstantPool()
        {
            m_entries.emplace_back(NullInfo());
        }

        [[nodiscard]] constexpr auto size() const -> size_t { return m_entries.size(); }
        [[nodiscard]] constexpr auto allEntries() const -> const std::vector<PoolEntry>& { return m_entries; }
        [[nodiscard]] constexpr auto realEntries() const
        {
            return m_entries | std::views::filter([](const PoolEntry& e) { return !std::holds_alternative<NullInfo>(e); });
        }

        [[nodiscard]] constexpr auto operator[](const size_t index) const -> const PoolEntry& { return m_entries[index]; }
        [[nodiscard]] constexpr auto get(const size_t index) const
            -> std::expected<std::reference_wrapper<const PoolEntry>, std::string>
        {
            if (index >= m_entries.size() || index == 0)
                return std::unexpected(std::format("Index {} is out of bounds [{}, {}]", index, 1, m_entries.size() - 1));
            return m_entries[index];
        }

        [[nodiscard]] constexpr auto entryHasTag(const size_t index, const Tag tag) const -> bool
        {
            if (index >= m_entries.size()) return false;
            return tagFromEntry(m_entries[index]) == tag;
        }

        constexpr auto addEntry(PoolEntry entry) -> PoolEntry&
        {
            if (const auto tag = tagFromEntry(entry); tag == Tag::Long || tag == Tag::Double)
            {
                auto& newEntry = m_entries.emplace_back(std::move(entry));
                m_entries.emplace_back(NullInfo());
                return newEntry;
            }
            return m_entries.emplace_back(std::move(entry));
        }

        [[nodiscard]] constexpr auto getUtf8(const size_t index) const -> std::expected<std::string_view, std::string>
        {
            const auto entry = get(index);
            if (!entry.has_value()) return std::unexpected(entry.error());
            if (!std::holds_alternative<Utf8Info>(entry->get()))
                return std::unexpected(generateUnexpectedTypeMessage("UTF8", index));
            return std::get<Utf8Info>(entry->get()).bytes;
        }

        [[nodiscard]] constexpr auto getClassInfo(const size_t index) const -> std::expected<ResolvedClassInfo, std::string>
        {
            const auto entry = get(index);
            if (!entry.has_value()) return std::unexpected(entry.error());
            if (!std::holds_alternative<ClassInfo>(entry->get()))
                return std::unexpected(generateUnexpectedTypeMessage("Class", index));
            const auto& [nameIndex] = std::get<ClassInfo>(entry->get());
            const auto className = getUtf8(nameIndex);
            if (!className.has_value())
                return std::unexpected(generateUnableToGetMessage("class name", nameIndex, className.error()));
            return ResolvedClassInfo{ .name = *className };
        }

        [[nodiscard]] constexpr auto getStringInfo(const size_t index) const -> std::expected<std::string_view, std::string>
        {
            const auto entry = get(index);
            if (!entry.has_value()) return std::unexpected(entry.error());
            if (!std::holds_alternative<StringInfo>(entry->get()))
                return std::unexpected(generateUnexpectedTypeMessage("String", index));
            const auto& [stringIndex] = std::get<StringInfo>(entry->get());
            const auto string = getUtf8(stringIndex);
            if (!string.has_value())
                return std::unexpected(generateUnableToGetMessage("string", stringIndex, string.error()));
            return *string;
        }

        [[nodiscard]] constexpr auto getFieldrefInfo(const size_t index) const -> std::expected<ResolvedFieldrefInfo, std::string>
        {
            const auto entry = get(index);
            if (!entry.has_value()) return std::unexpected(entry.error());
            if (!std::holds_alternative<FieldrefInfo>(entry->get()))
                return std::unexpected(generateUnexpectedTypeMessage("Fieldref", index));
            const auto& [classIndex, nameAndTypeIndex] = std::get<FieldrefInfo>(entry->get());

            const auto className = getClassInfo(classIndex);
            if (!className.has_value())
                return std::unexpected(generateUnableToGetMessage("class name", classIndex, className.error()));

            const auto nameAndType = getNameAndTypeInfo(nameAndTypeIndex);
            if (!nameAndType.has_value())
                return std::unexpected(generateUnableToGetMessage("name and type", nameAndTypeIndex, nameAndType.error()));

            return ResolvedFieldrefInfo{ .className = className->name, .name = nameAndType->name, .type = nameAndType->type };
        }

        [[nodiscard]] constexpr auto getMethodrefInfo(const size_t index) const -> std::expected<ResolvedMethodrefInfo, std::string>
        {
            const auto entry = get(index);
            if (!entry.has_value()) return std::unexpected(entry.error());
            if (!std::holds_alternative<MethodrefInfo>(entry->get()))
                return std::unexpected(generateUnexpectedTypeMessage("Methodref", index));
            const auto& [classIndex, nameAndTypeIndex] = std::get<MethodrefInfo>(entry->get());

            const auto className = getClassInfo(classIndex);
            if (!className.has_value())
                return std::unexpected(generateUnableToGetMessage("class name", classIndex, className.error()));

            const auto nameAndType = getNameAndTypeInfo(nameAndTypeIndex);
            if (!nameAndType.has_value())
                return std::unexpected(generateUnableToGetMessage("name and type", nameAndTypeIndex, nameAndType.error()));

            return ResolvedMethodrefInfo{ .className = className->name, .name = nameAndType->name, .type = nameAndType->type };
        }

        [[nodiscard]] constexpr auto getInterfaceMethodrefInfo(const size_t index) const -> std::expected<ResolvedInterfaceMethodrefInfo, std::string>
        {
            const auto entry = get(index);
            if (!entry.has_value()) return std::unexpected(entry.error());
            if (!std::holds_alternative<InterfaceMethodrefInfo>(entry->get()))
                return std::unexpected(generateUnexpectedTypeMessage("InterfaceMethodref", index));
            const auto& [classIndex, nameAndTypeIndex] = std::get<MethodrefInfo>(entry->get());

            const auto className = getClassInfo(classIndex);
            if (!className.has_value())
                return std::unexpected(generateUnableToGetMessage("class name", classIndex, className.error()));

            const auto nameAndType = getNameAndTypeInfo(nameAndTypeIndex);
            if (!nameAndType.has_value())
                return std::unexpected(generateUnableToGetMessage("name and type", nameAndTypeIndex, nameAndType.error()));

            return ResolvedInterfaceMethodrefInfo{ .className = className->name, .name = nameAndType->name, .type = nameAndType->type };
        }

        [[nodiscard]] constexpr auto getNameAndTypeInfo(const size_t index) const -> std::expected<ResolvedNameAndTypeInfo, std::string>
        {
            const auto entry = get(index);
            if (!entry.has_value()) return std::unexpected(entry.error());
            if (!std::holds_alternative<NameAndTypeInfo>(entry->get()))
                return std::unexpected(generateUnexpectedTypeMessage("NameAndType", index));
            const auto& [nameIndex, descriptorIndex] = std::get<NameAndTypeInfo>(entry->get());

            const auto name = getUtf8(nameIndex);
            if (!name.has_value())
                return std::unexpected(std::format("Unable to get name at index {}. {}", nameIndex, name.error()));

            const auto descriptor = getUtf8(descriptorIndex);
            if (!descriptor.has_value())
                return std::unexpected(std::format("Unable to get descriptor at index {}. {}", nameIndex, name.error()));

            return ResolvedNameAndTypeInfo{ .name = *name, .type = *descriptor };
        }
    };
}