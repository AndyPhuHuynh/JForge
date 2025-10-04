#pragma once

#include <cstdint>

namespace jforge
{
    enum class OpCode : uint8_t
    {
        none          = 0x00,
        ldc           = 0x12,
        ret           = 0xb1,
        getstatic     = 0xb2,
        invokevirtual = 0xb6,
    };

    constexpr auto opCodeFromNum(const uint8_t opcode) -> OpCode
    {
        switch (opcode)
        {
        case 0x12: return OpCode::ldc;
        case 0xb1: return OpCode::ret;
        case 0xb2: return OpCode::getstatic;
        case 0xb6: return OpCode::invokevirtual;
        default:   return OpCode::none;
        }
    }
}