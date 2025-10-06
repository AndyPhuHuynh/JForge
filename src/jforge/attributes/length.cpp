#include "jforge/attributes/length.hpp"

namespace jforge::attributes
{
    auto calculateCodeLength(const Code& code) -> uint32_t
    {
        constexpr uint32_t maxStackLen = 2;
        constexpr uint32_t maxLocalsLen = 2;
        constexpr uint32_t codeLengthLen = 4;

        constexpr uint32_t exceptionTableLengthLen = 2;
        constexpr uint32_t exceptionTableEntryLen = 8;

        constexpr uint32_t attributesCountLen = 2;
        constexpr uint32_t staticLen = maxStackLen + maxLocalsLen + codeLengthLen + exceptionTableLengthLen +  attributesCountLen;

        return staticLen + code.codeLength + (code.exceptionTableLength * exceptionTableEntryLen);
    }
}
