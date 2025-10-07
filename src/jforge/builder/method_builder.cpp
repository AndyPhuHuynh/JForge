#include "jforge/builder/method_builder.hpp"

#include "jforge/attributes/length.hpp"
#include "jforge/attributes/names.hpp"
#include "jforge/builder/attribute_builder.hpp"

namespace jforge::builder
{
    MethodBuilder::MethodBuilder(
        const access::Method accessFlags,
        const std::string_view name,
        const std::string_view descriptor)
        : m_accessFlags(accessFlags), m_name(name), m_descriptor(descriptor) {}

    auto MethodBuilder::getAccessFlags() const -> access::Method
    {
        return m_accessFlags;
    }

    auto MethodBuilder::getName() const -> const std::string&
    {
        return m_name;
    }

    auto MethodBuilder::getDescriptor() const -> const std::string&
    {
        return m_descriptor;
    }

    auto MethodBuilder::getInstructions() const -> const std::vector<Instructions>&
    {
        return m_instructions;
    }

    void MethodBuilder::ldcString(const std::string_view str)
    {
        m_instructions.emplace_back(std::in_place_type<LdcString>, LdcString { .value = std::string(str) });
    }

    void MethodBuilder::aload0()
    {
        m_instructions.emplace_back(ALoad0{});
    }

    void MethodBuilder::aload1()
    {
        m_instructions.emplace_back(ALoad1{});
    }

    void MethodBuilder::aload2()
    {
        m_instructions.emplace_back(ALoad2{});
    }

    void MethodBuilder::aload3()
    {
        m_instructions.emplace_back(ALoad3{});
    }

    void MethodBuilder::ret()
    {
        m_instructions.emplace_back(Ret{});
    }

    void MethodBuilder::getstatic(
        const std::string_view className,
        const std::string_view fieldName,
        const std::string_view descriptor)
    {
        m_instructions.emplace_back(
            std::in_place_type<GetStatic>,
            GetStatic {
                .className  = std::string(className),
                .fieldName  = std::string(fieldName),
                .descriptor = std::string(descriptor)
            }
        );
    }

    void MethodBuilder::invokevirtual(
        const std::string_view className,
        const std::string_view methodName,
        const std::string_view descriptor)
    {
        m_instructions.emplace_back(
            std::in_place_type<InvokeVirtual>,
            InvokeVirtual {
                .className  = std::string(className),
                .methodName = std::string(methodName),
                .descriptor = std::string(descriptor)
            }
        );
    }

    void MethodBuilder::invokespecial(
        const std::string_view className,
        const std::string_view methodName,
        const std::string_view descriptor)
    {
        m_instructions.emplace_back(
            std::in_place_type<InvokeSpecial>,
            InvokeSpecial {
                .className  = std::string(className),
                .methodName = std::string(methodName),
                .descriptor = std::string(descriptor)
            }
        );
    }

    auto MethodBuilder::build(const constant_pool::ConstantPool& cp) const -> std::expected<classfile::MethodInfo, std::string>
    {
        classfile::MethodInfo info;
        info.accessFlags = static_cast<uint16_t>(m_accessFlags);

        const auto nameIndex = cp.getUtf8Index(m_name);
        if (!nameIndex)
            return std::unexpected(std::format("Unable to create method \"{}\": {}", m_name, nameIndex.error()));
        info.nameIndex = *nameIndex;

        const auto descriptorIndex = cp.getUtf8Index(m_descriptor);
        if (!descriptorIndex)
            return std::unexpected(std::format("Unable to create method \"{}\": {}", m_name, descriptorIndex.error()));
        info.descriptorIndex = *descriptorIndex;

        const auto attrName = cp.getUtf8Index(attributes::CodeID);
        if (!attrName)
            return std::unexpected(std::format("Unable to create method \"{}\": {}", m_name, attrName.error()));

        auto code = generateCodeAttribute(cp, m_instructions);
        if (!code)
            return std::unexpected(std::format("Unable to create method \"{}\": {}", m_name, code.error()));

        attributes::AttributeInfo codeAttr {
            .nameIndex = *attrName,
            .length = attributes::calculateCodeLength(*code),
            .value = std::move(*code)
        };
        info.attributes.emplace_back(std::move(codeAttr));
        info.attributeCounts = info.attributes.size();

        return info;
    }
}
