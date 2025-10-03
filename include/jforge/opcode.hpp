#pragma once

#include <cstdint>

namespace jforge
{
    enum class OpCode : uint8_t
    {
        none      = 0x00,
        getstatic = 0xb2,
    };

    constexpr auto opCodeFromNum(const uint8_t opcode) -> OpCode
    {
        switch (opcode)
        {
            case 0xb2: return OpCode::getstatic;
            default:   return OpCode::none;
        }
    }
}