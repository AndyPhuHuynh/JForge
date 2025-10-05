#pragma once

#include <cstdint>

namespace jforge
{
    enum class OpCode : uint8_t
    {
        none          = 0x00,
        ldc           = 0x12,
        aload_0       = 0x2a,
        aload_1       = 0x2b,
        aload_2       = 0x2c,
        aload_3       = 0x2d,
        ret           = 0xb1,
        getstatic     = 0xb2,
        invokevirtual = 0xb6,
        invokespecial = 0xb7,
    };

    constexpr auto opCodeFromNum(const uint8_t opcode) -> OpCode
    {
        switch (opcode)
        {
        case 0x12: return OpCode::ldc;
        case 0x2a: return OpCode::aload_0;
        case 0x2b: return OpCode::aload_1;
        case 0x2c: return OpCode::aload_2;
        case 0x2d: return OpCode::aload_3;
        case 0xb1: return OpCode::ret;
        case 0xb2: return OpCode::getstatic;
        case 0xb6: return OpCode::invokevirtual;
        case 0xb7: return OpCode::invokespecial;
        default:   return OpCode::none;
        }
    }
}