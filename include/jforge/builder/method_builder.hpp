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

        void aconst_null();

        void iconst_m1();
        void iconst_0();
        void iconst_1();
        void iconst_2();
        void iconst_3();
        void iconst_4();
        void iconst_5();

        void lconst_0();
        void lconst_1();

        void fconst_0();
        void fconst_1();
        void fconst_2();

        void dconst_0();
        void dconst_1();

        void bipush(int8_t value);
        void sipush(int16_t value);

        void ldcInt(int32_t value);
        void ldcFloat(float value);
        void ldcLong(int64_t value);
        void ldcDouble(double value);
        void ldcClass(std::string_view className);
        void ldcString(std::string_view str);

        void iload0();
        void iload1();
        void iload2();
        void iload3();

        void aload0();
        void aload1();
        void aload2();
        void aload3();

        void istore0();
        void istore1();
        void istore2();
        void istore3();

        void iadd();
        void isub();
        void imul();
        void idiv();
        void irem();
        void ret();
        void getstatic(std::string_view className, std::string_view fieldName, std::string_view descriptor);
        void invokevirtual(std::string_view className, std::string_view methodName, std::string_view descriptor);
        void invokespecial(std::string_view className, std::string_view methodName, std::string_view descriptor);
        void invokestatic(std::string_view className, std::string_view methodName, std::string_view descriptor);

    private:
        [[nodiscard]] auto build(const constant_pool::ConstantPool& cp) const -> std::expected<classfile::MethodInfo, std::string>;
    };
}
