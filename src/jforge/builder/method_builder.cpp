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

    auto MethodBuilder::getInstructions() const -> const std::vector<bytecode::Instructions>&
    {
        return m_instructions;
    }

    void MethodBuilder::aconst_null()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::aconst_null });
    }

    void MethodBuilder::iconst_m1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iconst_m1 });
    }

    void MethodBuilder::iconst_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iconst_0 });
    }

    void MethodBuilder::iconst_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iconst_1 });
    }

    void MethodBuilder::iconst_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iconst_2 });
    }

    void MethodBuilder::iconst_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iconst_3 });
    }

    void MethodBuilder::iconst_4()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iconst_4 });
    }

    void MethodBuilder::iconst_5()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iconst_5 });
    }

    void MethodBuilder::lconst_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::lconst_0 });
    }

    void MethodBuilder::lconst_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::lconst_1 });
    }

    void MethodBuilder::fconst_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::fconst_0 });
    }

    void MethodBuilder::fconst_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::fconst_1 });
    }

    void MethodBuilder::fconst_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::fconst_2 });
    }

    void MethodBuilder::dconst_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::dconst_0 });
    }

    void MethodBuilder::dconst_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::dconst_1 });
    }

    void MethodBuilder::bipush(const int8_t value)
    {
        m_instructions.emplace_back(bytecode::InstructionOneArgInt8 { bytecode::OpCode::bipush, value });
    }

    void MethodBuilder::sipush(const int16_t value)
    {
        m_instructions.emplace_back(bytecode::InstructionOneArgInt16 { bytecode::OpCode::sipush, value });
    }

    void MethodBuilder::ldcInt(const int32_t value)
    {
        m_instructions.emplace_back(bytecode::InstructionLdcInt { value });
    }

    void MethodBuilder::ldcFloat(const float value)
    {
        m_instructions.emplace_back(bytecode::InstructionLdcFloat { value });
    }

    void MethodBuilder::ldcLong(const int64_t value)
    {
        m_instructions.emplace_back(bytecode::InstructionLdcLong { value });
    }

    void MethodBuilder::ldcDouble(const double value)
    {
        m_instructions.emplace_back(bytecode::InstructionLdcDouble { value });
    }

    void MethodBuilder::ldcClass(const std::string_view className)
    {
        m_instructions.emplace_back(bytecode::InstructionLdcClass { .className = std::string(className) });
    }

    void MethodBuilder::ldcString(const std::string_view str)
    {
        m_instructions.emplace_back(bytecode::InstructionLdcString { .value = std::string(str) });
    }

    void MethodBuilder::iload(const uint8_t index)
    {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::iload, .value = index });
    }

    void MethodBuilder::lload(const uint8_t index)
    {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::lload, .value = index });
    }

    void MethodBuilder::fload(const uint8_t index)
    {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::fload, .value = index });
    }

    void MethodBuilder::dload(const uint8_t index)
    {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::dload, .value = index });
    }

    void MethodBuilder::aload(const uint8_t index)
    {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::aload, .value = index });
    }

    void MethodBuilder::iload_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iload_0 });
    }

    void MethodBuilder::iload_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iload_1 });
    }

    void MethodBuilder::iload_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iload_2 });
    }

    void MethodBuilder::iload_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::iload_3 });
    }

    void MethodBuilder::lload_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::lload_0 });
    }

    void MethodBuilder::lload_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::lload_1 });
    }

    void MethodBuilder::lload_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::lload_2 });
    }

    void MethodBuilder::lload_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::lload_3 });
    }

    void MethodBuilder::fload_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::fload_0 });
    }

    void MethodBuilder::fload_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::fload_1 });
    }

    void MethodBuilder::fload_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::fload_2 });
    }

    void MethodBuilder::fload_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::fload_3 });
    }

    void MethodBuilder::dload_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::dload_0 });
    }

    void MethodBuilder::dload_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::dload_1 });
    }

    void MethodBuilder::dload_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::dload_2 });
    }

    void MethodBuilder::dload_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::dload_3 });
    }

    void MethodBuilder::aload_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::aload_0 });
    }

    void MethodBuilder::aload_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::aload_1 });
    }

    void MethodBuilder::aload_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::aload_2 });
    }

    void MethodBuilder::aload_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::aload_3 });
    }

    void MethodBuilder::iaload() {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::iaload });
    }

    void MethodBuilder::laload() {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::laload });
    }

    void MethodBuilder::faload() {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::faload });
    }

    void MethodBuilder::daload() {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::daload });
    }

    void MethodBuilder::aaload() {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::aaload });
    }

    void MethodBuilder::baload() {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::baload });
    }

    void MethodBuilder::caload() {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::caload });
    }

    void MethodBuilder::saload() {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::saload });
    }

    void MethodBuilder::istore(const uint8_t index) {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::istore, .value = index });
    }

    void MethodBuilder::lstore(const uint8_t index) {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::lstore, .value = index });
    }

    void MethodBuilder::fstore(const uint8_t index) {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::fstore, .value = index });
    }

    void MethodBuilder::dstore(const uint8_t index) {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::dstore, .value = index });
    }

    void MethodBuilder::astore(const uint8_t index) {
        m_instructions.emplace_back(bytecode::InstructionOneArgUInt8 { .opcode = bytecode::OpCode::astore, .value = index });
    }

    void MethodBuilder::istore_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::istore_0 });
    }

    void MethodBuilder::istore_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::istore_1 });
    }

    void MethodBuilder::istore_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::istore_2 });
    }

    void MethodBuilder::istore_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::istore_3 });
    }

    void MethodBuilder::lstore_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lstore_0 });
    }

    void MethodBuilder::lstore_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lstore_1 });
    }

    void MethodBuilder::lstore_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lstore_2 });
    }

    void MethodBuilder::lstore_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lstore_3 });
    }

    void MethodBuilder::fstore_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fstore_0 });
    }

    void MethodBuilder::fstore_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fstore_1 });
    }

    void MethodBuilder::fstore_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fstore_2 });
    }

    void MethodBuilder::fstore_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fstore_3 });
    }

    void MethodBuilder::dstore_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dstore_0 });
    }

    void MethodBuilder::dstore_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dstore_1 });
    }

    void MethodBuilder::dstore_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dstore_2 });
    }

    void MethodBuilder::dstore_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dstore_3 });
    }

    void MethodBuilder::astore_0()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::astore_0 });
    }

    void MethodBuilder::astore_1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::astore_1 });
    }

    void MethodBuilder::astore_2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::astore_2 });
    }

    void MethodBuilder::astore_3()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::astore_3 });
    }

    void MethodBuilder::iastore()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::iastore });
    }

    void MethodBuilder::lastore()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lastore });
    }

    void MethodBuilder::fastore()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fastore });
    }

    void MethodBuilder::dastore()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dastore });
    }

    void MethodBuilder::aastore()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::aastore });
    }

    void MethodBuilder::bastore()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::bastore });
    }

    void MethodBuilder::castore()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::castore });
    }

    void MethodBuilder::sastore()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::sastore });
    }

    void MethodBuilder::pop()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::pop });
    }

    void MethodBuilder::pop2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::pop2 });
    }

    void MethodBuilder::dup()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dup });
    }

    void MethodBuilder::dup_x1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dup_x1 });
    }

    void MethodBuilder::dup_x2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dup_x2 });
    }

    void MethodBuilder::dup2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dup2 });
    }

    void MethodBuilder::dup2_x1()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dup2_x1 });
    }

    void MethodBuilder::dup2_x2()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dup2_x2 });
    }

    void MethodBuilder::swap()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::swap });
    }

    void MethodBuilder::iadd()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::iadd });
    }

    void MethodBuilder::ladd()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::ladd });
    }

    void MethodBuilder::fadd()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fadd });
    }

    void MethodBuilder::dadd()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dadd });
    }

    void MethodBuilder::isub()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::isub });
    }

    void MethodBuilder::lsub()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lsub });
    }

    void MethodBuilder::fsub()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fsub });
    }

    void MethodBuilder::dsub()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dsub });
    }

    void MethodBuilder::imul()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::imul });
    }

    void MethodBuilder::lmul()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lmul });
    }

    void MethodBuilder::fmul()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fmul });
    }

    void MethodBuilder::dmul()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dmul });
    }

    void MethodBuilder::idiv()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::idiv });
    }

    void MethodBuilder::ldiv()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::ldiv });
    }

    void MethodBuilder::fdiv()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fdiv });
    }

    void MethodBuilder::ddiv()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::ddiv });
    }

    void MethodBuilder::irem()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::irem });
    }

    void MethodBuilder::lrem()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lrem });
    }

    void MethodBuilder::frem()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::frem });
    }

    void MethodBuilder::drem()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::drem });
    }

    void MethodBuilder::ineg()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::ineg });
    }

    void MethodBuilder::lneg()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lneg });
    }

    void MethodBuilder::fneg()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::fneg });
    }

    void MethodBuilder::dneg()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::dneg });
    }

    void MethodBuilder::ishl()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::ishl });
    }

    void MethodBuilder::lshl()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lshl });
    }

    void MethodBuilder::ishr()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::ishr });
    }

    void MethodBuilder::lshr()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lshr });
    }
    void MethodBuilder::iushr()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::iushr });
    }

    void MethodBuilder::lushr()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lushr });
    }

    void MethodBuilder::iand()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::iand });
    }

    void MethodBuilder::land()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::land });
    }

    void MethodBuilder::ior()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::ior });
    }

    void MethodBuilder::lor()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lor });
    }

    void MethodBuilder::ixor()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::ixor });
    }

    void MethodBuilder::lxor()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg { bytecode::OpCode::lxor });
    }

    void MethodBuilder::iinc(const uint8_t index, const uint8_t increment)
    {
        m_instructions.emplace_back(bytecode::InstructionIINC { .index = index, .increment = increment });
    }

    void MethodBuilder::i2l()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::i2l });
    }

    void MethodBuilder::i2f()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::i2f });
    }

    void MethodBuilder::i2d()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::i2d });
    }

    void MethodBuilder::l2i()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::l2i });
    }

    void MethodBuilder::l2f()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::l2f });
    }

    void MethodBuilder::l2d()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::l2d });
    }

    void MethodBuilder::f2i()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::f2i });
    }

    void MethodBuilder::f2l()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::f2l });
    }

    void MethodBuilder::f2d()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::f2d });
    }

    void MethodBuilder::d2i()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::d2i });
    }

    void MethodBuilder::d2l()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::d2l });
    }

    void MethodBuilder::d2f()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::d2f });
    }

    void MethodBuilder::i2b()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::i2b });
    }

    void MethodBuilder::i2c()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::i2c });
    }

    void MethodBuilder::i2s()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::i2s });
    }

    void MethodBuilder::lcmp()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::lcmp });
    }

    void MethodBuilder::fcmpl()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::fcmpl });
    }

    void MethodBuilder::fcmpg()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::fcmpg });
    }

    void MethodBuilder::dcmpl()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::dcmpl });
    }

    void MethodBuilder::dcmpg()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::dcmpg });
    }

    void MethodBuilder::ret()
    {
        m_instructions.emplace_back(bytecode::InstructionNoArg{ bytecode::OpCode::ret });
    }

    void MethodBuilder::getstatic(
        const std::string_view className,
        const std::string_view fieldName,
        const std::string_view descriptor)
    {
        m_instructions.emplace_back(
            bytecode::InstructionFieldArg {
                .opcode     = bytecode::OpCode::getstatic,
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
            bytecode::InstructionMethodArg {
                .opcode     = bytecode::OpCode::invokevirtual,
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
            bytecode::InstructionMethodArg {
                .opcode     = bytecode::OpCode::invokespecial,
                .className  = std::string(className),
                .methodName = std::string(methodName),
                .descriptor = std::string(descriptor)
            }
        );
    }

    void MethodBuilder::invokestatic(
        const std::string_view className,
        const std::string_view methodName,
        const std::string_view descriptor)
    {
        m_instructions.emplace_back(
           bytecode::InstructionMethodArg {
               .opcode     = bytecode::OpCode::invokestatic,
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
