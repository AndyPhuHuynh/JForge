#include "jforge/constant_pool/constant_pool.hpp"

#include <ranges>

#include "jforge/constant_pool/hash.hpp"

namespace
{
    [[nodiscard]] constexpr auto generateUnexpectedTypeMessage(std::string_view entryType, const size_t index) -> std::string
    {
        return std::format("Attempted to get {} info at index {}. Entry is not a {} info", entryType, index, entryType);
    }

    [[nodiscard]] constexpr auto generateUnableToGetMessage(std::string_view name, const size_t index, std::string_view nestedError) -> std::string
    {
        return std::format("Unable to get {} at index {}. {}", name, index, nestedError);
    }
}

namespace jforge::constant_pool
{
    ConstantPool::ConstantPool()
    {
        m_entries.emplace_back(NullInfo());
    }

    auto ConstantPool::size() const -> size_t
    {
        return m_entries.size();
    }

    auto ConstantPool::allEntries() const -> const std::vector<PoolEntry>&
    {
        return m_entries;
    }

    auto ConstantPool::realEntries() const
    {
        return m_entries | std::views::filter([](const PoolEntry& e) { return !std::holds_alternative<NullInfo>(e); });
    }

    auto ConstantPool::operator[](const size_t index) const -> const PoolEntry&
    {
        return m_entries[index];
    }

    auto ConstantPool::get(size_t index) const -> std::expected<std::reference_wrapper<const PoolEntry>, std::string>
    {
        if (index >= m_entries.size() || index == 0)
            return std::unexpected(std::format("Index {} is out of bounds [{}, {}]", index, 1, m_entries.size() - 1));
        if (std::holds_alternative<NullInfo>(m_entries[index]))
            return std::unexpected(std::format("Index {} contains a null entry after a long or double", index));
        return m_entries[index];
    }

    auto ConstantPool::addEntry(PoolEntry entry) -> PoolEntry&
    {
        if (const auto tag = tagFromEntry(entry); tag == Tag::Long || tag == Tag::Double)
        {
            auto& newEntry = m_entries.emplace_back(std::move(entry));
            m_entries.emplace_back(NullInfo());
            return newEntry;
        }
        return m_entries.emplace_back(std::move(entry));
    }

    auto ConstantPool::getUtf8(const size_t index) const -> std::expected<std::string_view, std::string>
    {
        const auto entry = get(index);
        if (!entry.has_value()) return std::unexpected(entry.error());
        if (!std::holds_alternative<Utf8Info>(entry->get()))
            return std::unexpected(generateUnexpectedTypeMessage("UTF8", index));
        return std::get<Utf8Info>(entry->get()).bytes;
    }

    auto ConstantPool::getClassInfo(const size_t index) const -> std::expected<ResolvedClassInfo, std::string>
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

    auto ConstantPool::resolveStringInfo(const StringInfo& info) const -> std::expected<std::string_view, std::string>
    {
        const auto& [stringIndex] = info;
        const auto string = getUtf8(stringIndex);
        if (!string.has_value())
            return std::unexpected(generateUnableToGetMessage("string", stringIndex, string.error()));
        return *string;
    }

    auto ConstantPool::getStringInfo(const size_t index) const -> std::expected<std::string_view, std::string>
    {
        const auto entry = get(index);
        if (!entry.has_value()) return std::unexpected(entry.error());
        if (!std::holds_alternative<StringInfo>(entry->get()))
            return std::unexpected(generateUnexpectedTypeMessage("String", index));
        return resolveStringInfo(std::get<StringInfo>(entry->get()));
    }

    auto ConstantPool::getFieldrefInfo(const size_t index) const -> std::expected<ResolvedFieldrefInfo, std::string>
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

    auto ConstantPool::getMethodrefInfo(
        const size_t index) const -> std::expected<ResolvedMethodrefInfo, std::string>
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

    auto ConstantPool::getInterfaceMethodrefInfo(
        const size_t index) const -> std::expected<ResolvedInterfaceMethodrefInfo, std::string>
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

    auto ConstantPool::getNameAndTypeInfo(
        const size_t index) const -> std::expected<ResolvedNameAndTypeInfo, std::string>
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

    auto ConstantPool::addUtf8(const std::string_view value) -> uint16_t
    {
        const uint64_t hash = hashUtf8(value);
        if (m_utf8Entries.contains(hash))
            return m_utf8Entries.at(hash);
        const auto index = static_cast<uint16_t>(m_entries.size());
        m_utf8Entries.emplace(hash, index);
        m_entries.emplace_back(Utf8Info{ .length = static_cast<uint16_t>(value.length()), .bytes = std::string(value) });
        return index;
    }

    auto ConstantPool::addClass(const std::string_view className) -> uint16_t
    {
        const uint64_t hash = hashClass(className);
        if (m_classEntries.contains(hash))
            return m_classEntries.at(hash);

        const uint16_t nameIndex = addUtf8(className);
        m_entries.emplace_back(ClassInfo{ .nameIndex = nameIndex });

        const auto index = static_cast<uint16_t>(m_entries.size() - 1);
        m_classEntries.emplace(hash, index);
        return index;
    }

    auto ConstantPool::addString(const std::string_view value) -> uint16_t
    {
        const uint64_t hash = hashString(value);
        if (m_stringEntries.contains(hash))
            return m_stringEntries.at(hash);
        m_entries.emplace_back(StringInfo{ .stringIndex = addUtf8(value) });

        const auto index = static_cast<uint16_t>(m_entries.size() - 1);
        m_stringEntries.emplace(hash, index);
        return index;
    }

    auto ConstantPool::addFieldref(
        const std::string_view className,
        const std::string_view fieldName,
        const std::string_view descriptor) -> uint16_t
    {
        const uint64_t hash = hashFieldref(className, fieldName, descriptor);
        if (m_fieldrefEntries.contains(hash))
            return m_fieldrefEntries.at(hash);

        const uint16_t classIndex = addClass(className);
        const uint16_t nameAndTypeIndex = addNameAndType(fieldName, descriptor);
        m_entries.emplace_back(FieldrefInfo{ .classIndex = classIndex, .nameAndTypeIndex = nameAndTypeIndex });

        const auto index = static_cast<uint16_t>(m_entries.size() - 1);
        m_fieldrefEntries.emplace(hash, index);
        return index;
    }

    auto ConstantPool::addMethodref(
        const std::string_view className,
        const std::string_view methodName,
        const std::string_view descriptor) -> uint16_t
    {
        const uint64_t hash = hashMethodref(className, methodName, descriptor);
        if (m_methodrefEntries.contains(hash))
            return m_methodrefEntries.at(hash);

        const uint16_t classIndex = addClass(className);
        const uint16_t nameAndTypeIndex = addNameAndType(methodName, descriptor);
        m_entries.emplace_back(MethodrefInfo{ .classIndex = classIndex, .nameAndTypeIndex = nameAndTypeIndex });

        const auto index = static_cast<uint16_t>(m_entries.size() - 1);
        m_methodrefEntries.emplace(hash, index);
        return index;
    }

    auto ConstantPool::addInterfaceMethodref(
        const std::string_view className,
        const std::string_view interfaceMethodName,
        const std::string_view descriptor) -> uint16_t
    {
        const uint64_t hash = hashInterfaceMethodref(className, interfaceMethodName, descriptor);
        if (m_interfaceMethodrefEntries.contains(hash))
            return m_interfaceMethodrefEntries.at(hash);

        const uint16_t classIndex = addClass(className);
        const uint16_t nameAndTypeIndex = addNameAndType(interfaceMethodName, descriptor);
        m_entries.emplace_back(InterfaceMethodrefInfo{ .classIndex = classIndex, .nameAndTypeIndex = nameAndTypeIndex });

        const auto index = static_cast<uint16_t>(m_entries.size() - 1);
        m_interfaceMethodrefEntries.emplace(hash, index);
        return index;
    }

    auto ConstantPool::addNameAndType(const std::string_view name, const std::string_view type) -> uint16_t
    {
        const uint64_t hash = hashNameAndType(name, type);
        if (m_nameAndTypeEntries.contains(hash))
            return m_nameAndTypeEntries.at(hash);

        const uint16_t nameIndex = addUtf8(name);
        const uint16_t typeIndex = addUtf8(type);
        m_entries.emplace_back(NameAndTypeInfo{ .nameIndex = nameIndex, .descriptorIndex = typeIndex });

        const auto index = static_cast<uint16_t>(m_entries.size() - 1);
        m_nameAndTypeEntries.emplace(hash, index);
        return index;
    }
}
