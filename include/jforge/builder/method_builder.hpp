#pragma once

#include <expected>
#include <string>
#include <vector>

#include "jforge/access/flags.hpp"
#include "jforge/bytecode/instructions.hpp"
#include "jforge/classfile/method.hpp"
#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::builder
{
    class MethodBuilder
    {
        friend class ClassBuilder;
        access::Method m_accessFlags;
        std::string m_name;
        std::string m_descriptor;
        std::vector<bytecode::Instructions> m_instructions;

    public:
        MethodBuilder(access::Method accessFlags, std::string_view name, std::string_view descriptor);

        [[nodiscard]] auto getAccessFlags() const -> access::Method;
        [[nodiscard]] auto getName() const -> const std::string&;
        [[nodiscard]] auto getDescriptor() const -> const std::string&;
        [[nodiscard]] auto getInstructions() const -> const std::vector<bytecode::Instructions>&;

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

        void iload(uint8_t index);
        void lload(uint8_t index);
        void fload(uint8_t index);
        void dload(uint8_t index);
        void aload(uint8_t index);

        void iload_0();
        void iload_1();
        void iload_2();
        void iload_3();

        void lload_0();
        void lload_1();
        void lload_2();
        void lload_3();

        void fload_0();
        void fload_1();
        void fload_2();
        void fload_3();

        void dload_0();
        void dload_1();
        void dload_2();
        void dload_3();

        void aload_0();
        void aload_1();
        void aload_2();
        void aload_3();

        void iaload();
        void laload();
        void faload();
        void daload();
        void aaload();
        void baload();
        void caload();
        void saload();

        void istore(uint8_t index);
        void lstore(uint8_t index);
        void fstore(uint8_t index);
        void dstore(uint8_t index);
        void astore(uint8_t index);

        void istore_0();
        void istore_1();
        void istore_2();
        void istore_3();

        void lstore_0();
        void lstore_1();
        void lstore_2();
        void lstore_3();

        void fstore_0();
        void fstore_1();
        void fstore_2();
        void fstore_3();

        void dstore_0();
        void dstore_1();
        void dstore_2();
        void dstore_3();

        void astore_0();
        void astore_1();
        void astore_2();
        void astore_3();

        void iastore();
        void lastore();
        void fastore();
        void dastore();
        void aastore();
        void bastore();
        void castore();
        void sastore();

        void pop();
        void pop2();
        void dup();
        void dup_x1();
        void dup_x2();
        void dup2();
        void dup2_x1();
        void dup2_x2();
        void swap();

        void iadd();
        void ladd();
        void fadd();
        void dadd();

        void isub();
        void lsub();
        void fsub();
        void dsub();

        void imul();
        void lmul();
        void fmul();
        void dmul();

        void idiv();
        void ldiv();
        void fdiv();
        void ddiv();

        void irem();
        void lrem();
        void frem();
        void drem();

        void ineg();
        void lneg();
        void fneg();
        void dneg();

        void ishl();
        void lshl();
        void ishr();
        void lshr();
        void iushr();
        void lushr();

        void iand();
        void land();
        void ior();
        void lor();
        void ixor();
        void lxor();

        void iinc(uint8_t index, uint8_t increment);

        void i2l();
        void i2f();
        void i2d();

        void l2i();
        void l2f();
        void l2d();

        void f2i();
        void f2l();
        void f2d();

        void d2i();
        void d2l();
        void d2f();

        void i2b();
        void i2c();
        void i2s();

        void lcmp();
        void fcmpl();
        void fcmpg();
        void dcmpl();
        void dcmpg();

        void ret();
        void getstatic(std::string_view className, std::string_view fieldName, std::string_view descriptor);
        void invokevirtual(std::string_view className, std::string_view methodName, std::string_view descriptor);
        void invokespecial(std::string_view className, std::string_view methodName, std::string_view descriptor);
        void invokestatic(std::string_view className, std::string_view methodName, std::string_view descriptor);

    private:
        [[nodiscard]] auto build(const constant_pool::ConstantPool& cp) const -> std::expected<classfile::MethodInfo, std::string>;
    };
}
