#pragma once

#include <expected>
#include <string>
#include <vector>

#include "jforge/access/flags.hpp"
#include "jforge/classfile/method.hpp"
#include "jforge/constant_pool/constant_pool.hpp"
#include "jforge/instructions.hpp"

namespace jforge::builder
{
    class MethodBuilder
    {
        access::Method m_accessFlags;
        std::string m_name;
        std::string m_descriptor;
        std::vector<Instructions> m_instructions;

    public:
        MethodBuilder(access::Method accessFlags, std::string_view name, std::string_view descriptor);

        [[nodiscard]] auto getAccessFlags() const -> access::Method;
        [[nodiscard]] auto getName() const -> const std::string&;
        [[nodiscard]] auto getDescriptor() const -> const std::string&;
        [[nodiscard]] auto getInstructions() const -> const std::vector<Instructions>&;

        void ldcString(std::string_view str);
        void getstatic(std::string_view className, std::string_view fieldName, std::string_view descriptor);
        void invokevirtual(std::string_view className, std::string_view methodName, std::string_view descriptor);

    private:
        auto build(const constant_pool::ConstantPool& cp) -> std::expected<classfile::MethodInfo, std::string>;
    };
}
