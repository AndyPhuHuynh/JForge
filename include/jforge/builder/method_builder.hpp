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
        friend class ClassBuilder;
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
        void aload0();
        void aload1();
        void aload2();
        void aload3();
        void ret();
        void getstatic(std::string_view className, std::string_view fieldName, std::string_view descriptor);
        void invokevirtual(std::string_view className, std::string_view methodName, std::string_view descriptor);
        void invokespecial(std::string_view className, std::string_view methodName, std::string_view descriptor);

    private:
        [[nodiscard]] auto build(const constant_pool::ConstantPool& cp) const -> std::expected<classfile::MethodInfo, std::string>;
    };
}
