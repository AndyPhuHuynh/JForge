#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <variant>
#include <vector>

#include "jforge/builder/refs.hpp"

namespace jforge::builder
{
    struct LdcString
    {
        std::string value;
    };

    struct GetStatic
    {
        std::string className;
        std::string fieldName;
        std::string descriptor;
    };

    struct InvokeVirtual
    {
        std::string className;
        std::string methodName;
        std::string descriptor;
    };

    using Instructions = std::variant<
        GetStatic,
        LdcString,
        InvokeVirtual
    >;

    class MethodBuilder
    {
        std::string m_name;
        std::string m_descriptor;
        std::vector<Instructions> m_instructions;
    public:
        MethodBuilder(std::string_view name, std::string_view descriptor);

        [[nodiscard]] auto getName() const -> const std::string&;
        [[nodiscard]] auto getDescriptor() const -> const std::string&;
        [[nodiscard]] auto getInstructions() const -> const std::vector<Instructions>&;

        void ldcString(std::string_view str);
        void getstatic(std::string_view className, std::string_view fieldName, std::string_view descriptor);
        void invokevirtual(std::string_view className, std::string_view methodName, std::string_view descriptor);
    };
}
