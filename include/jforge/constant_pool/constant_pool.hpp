#pragma once

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
    public:
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
        [[nodiscard]] constexpr auto get(const size_t index) const -> std::optional<std::reference_wrapper<const PoolEntry>>
        {
            if (index >= m_entries.size() || index == 0) return std::nullopt;
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

        [[nodiscard]] constexpr auto getUtf8(const size_t index) const -> std::expected<std::string, std::string>
        {
            const auto entry = get(index);
            if (!entry.has_value() || !std::holds_alternative<Utf8Info>(entry->get()))
                return std::unexpected(std::format("Unable to get UTF8 info from the constant pool at index {}", index));
            return std::get<Utf8Info>(entry->get()).bytes;
        }
    };
}