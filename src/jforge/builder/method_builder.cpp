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

    void MethodBuilder::aconst_null()
    {
        m_instructions.emplace_back(InstructionNoArg { OpCode::aconst_null });
    }

    void MethodBuilder::iconst_m1()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iconst_m1 });
    }

    void MethodBuilder::iconst_0()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iconst_0 });
    }

    void MethodBuilder::iconst_1()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iconst_1 });
    }

    void MethodBuilder::iconst_2()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iconst_2 });
    }

    void MethodBuilder::iconst_3()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iconst_3 });
    }

    void MethodBuilder::iconst_4()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iconst_4 });
    }

    void MethodBuilder::iconst_5()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iconst_5 });
    }

    void MethodBuilder::lconst_0()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::lconst_0 });
    }

    void MethodBuilder::lconst_1()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::lconst_1 });
    }

    void MethodBuilder::fconst_0()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::fconst_0 });
    }

    void MethodBuilder::fconst_1()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::fconst_1 });
    }

    void MethodBuilder::fconst_2()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::fconst_2 });
    }

    void MethodBuilder::dconst_0()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::dconst_0 });
    }

    void MethodBuilder::dconst_1()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::dconst_1 });
    }

    void MethodBuilder::bipush(const int8_t value)
    {
        m_instructions.emplace_back(InstructionOneArgInt8 { OpCode::bipush, value });
    }

    void MethodBuilder::sipush(const int16_t value)
    {
        m_instructions.emplace_back(InstructionOneArgInt16 { OpCode::sipush, value });
    }

    void MethodBuilder::ldcInt(const int32_t value)
    {
        m_instructions.emplace_back(InstructionLdcInt { value });
    }

    void MethodBuilder::ldcFloat(const float value)
    {
        m_instructions.emplace_back(InstructionLdcFloat { value });
    }

    void MethodBuilder::ldcLong(const int64_t value)
    {
        m_instructions.emplace_back(InstructionLdcLong { value });
    }

    void MethodBuilder::ldcDouble(const double value)
    {
        m_instructions.emplace_back(InstructionLdcDouble { value });
    }

    void MethodBuilder::ldcClass(const std::string_view className)
    {
        m_instructions.emplace_back(InstructionLdcClass { .className = std::string(className) });
    }

    void MethodBuilder::ldcString(const std::string_view str)
    {
        m_instructions.emplace_back(InstructionLdcString { .value = std::string(str) });
    }

    void MethodBuilder::iload0()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iload_0 });
    }

    void MethodBuilder::iload1()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iload_1 });
    }

    void MethodBuilder::iload2()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iload_2 });
    }

    void MethodBuilder::iload3()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iload_3 });
    }

    void MethodBuilder::aload0()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::aload_0 });
    }

    void MethodBuilder::aload1()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::aload_1 });
    }

    void MethodBuilder::aload2()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::aload_2 });
    }

    void MethodBuilder::aload3()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::aload_3 });
    }

    void MethodBuilder::istore0()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::istore_0 });
    }

    void MethodBuilder::istore1()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::istore_1 });
    }

    void MethodBuilder::istore2()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::istore_2 });
    }

    void MethodBuilder::istore3()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::istore_3 });
    }

    void MethodBuilder::iadd()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::iadd });
    }

    void MethodBuilder::isub()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::isub });
    }

    void MethodBuilder::imul()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::imul });
    }

    void MethodBuilder::idiv()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::idiv });
    }

    void MethodBuilder::irem()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::irem });
    }

    void MethodBuilder::ret()
    {
        m_instructions.emplace_back(InstructionNoArg{ OpCode::ret });
    }

    void MethodBuilder::getstatic(
        const std::string_view className,
        const std::string_view fieldName,
        const std::string_view descriptor)
    {
        m_instructions.emplace_back(
            InstructionFieldArg {
                .opcode     = OpCode::getstatic,
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
            InstructionMethodArg {
                .opcode     = OpCode::invokevirtual,
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
            InstructionMethodArg {
                .opcode     = OpCode::invokespecial,
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
           InstructionMethodArg {
               .opcode     = OpCode::invokestatic,
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
