#include "jforge/builder/method_builder.hpp"

namespace jforge::builder
{
    MethodBuilder::MethodBuilder(const std::string_view name, const std::string_view descriptor)
        : m_name(name), m_descriptor(descriptor) {}

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

    void MethodBuilder::getstatic(
        const std::string_view className,
        const std::string_view fieldName,
        const std::string_view descriptor)
    {
        m_instructions.emplace_back(
            std::in_place_type<GetStatic>,
            GetStatic{
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
}
