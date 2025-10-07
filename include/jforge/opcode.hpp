#pragma once

#include <cstdint>

namespace jforge
{
    enum class OpCode : uint8_t
    {
        none          = 0x00,
        aconst_null   = 0x01,
        iconst_m1     = 0x02,
        iconst_0      = 0x03,
        iconst_1      = 0x04,
        iconst_2      = 0x05,
        iconst_3      = 0x06,
        iconst_4      = 0x07,
        iconst_5      = 0x08,
        lconst_0      = 0x09,
        lconst_1      = 0x0a,
        fconst_0      = 0x0b,
        fconst_1      = 0x0c,
        fconst_2      = 0x0d,
        dconst_0      = 0x0e,
        dconst_1      = 0x0f,
        bipush        = 0x10,
        sipush        = 0x11,
        ldc           = 0x12,
        ldc_w         = 0x13,
        ldc2_w        = 0x14,
        iload_0       = 0x1a,
        iload_1       = 0x1b,
        iload_2       = 0x1c,
        iload_3       = 0x1d,
        aload_0       = 0x2a,
        aload_1       = 0x2b,
        aload_2       = 0x2c,
        aload_3       = 0x2d,
        istore_0      = 0x3b,
        istore_1      = 0x3c,
        istore_2      = 0x3d,
        istore_3      = 0x3e,
        iadd          = 0x60,
        isub          = 0x64,
        imul          = 0x68,
        idiv          = 0x6c,
        irem          = 0x70,
        ret           = 0xb1,
        getstatic     = 0xb2,
        invokevirtual = 0xb6,
        invokespecial = 0xb7,
        invokestatic  = 0xb8,
    };

    constexpr auto opCodeFromNum(const uint8_t opcode) -> OpCode
    {
        switch (opcode)
        {
        case 0x01: return OpCode::aconst_null;
        case 0x02: return OpCode::iconst_m1;
        case 0x03: return OpCode::iconst_0;
        case 0x04: return OpCode::iconst_1;
        case 0x05: return OpCode::iconst_2;
        case 0x06: return OpCode::iconst_3;
        case 0x07: return OpCode::iconst_4;
        case 0x08: return OpCode::iconst_5;
        case 0x09: return OpCode::lconst_0;
        case 0x0a: return OpCode::lconst_1;
        case 0x0b: return OpCode::fconst_0;
        case 0x0c: return OpCode::fconst_1;
        case 0x0d: return OpCode::fconst_2;
        case 0x0e: return OpCode::dconst_0;
        case 0x0f: return OpCode::dconst_1;
        case 0x10: return OpCode::bipush;
        case 0x11: return OpCode::sipush;
        case 0x12: return OpCode::ldc;
        case 0x13: return OpCode::ldc_w;
        case 0x14: return OpCode::ldc2_w;
        case 0x1a: return OpCode::iload_0;
        case 0x1b: return OpCode::iload_1;
        case 0x1c: return OpCode::iload_2;
        case 0x1d: return OpCode::iload_3;
        case 0x2a: return OpCode::aload_0;
        case 0x2b: return OpCode::aload_1;
        case 0x2c: return OpCode::aload_2;
        case 0x2d: return OpCode::aload_3;
        case 0x3b: return OpCode::istore_0;
        case 0x3c: return OpCode::istore_1;
        case 0x3d: return OpCode::istore_2;
        case 0x3e: return OpCode::istore_3;
        case 0x60: return OpCode::iadd;
        case 0x64: return OpCode::isub;
        case 0x68: return OpCode::imul;
        case 0x6c: return OpCode::idiv;
        case 0x70: return OpCode::irem;
        case 0xb1: return OpCode::ret;
        case 0xb2: return OpCode::getstatic;
        case 0xb6: return OpCode::invokevirtual;
        case 0xb7: return OpCode::invokespecial;
        case 0xb8: return OpCode::invokestatic;
        default:   return OpCode::none;
        }
    }

    constexpr auto opCodeToString(const OpCode opcode) -> std::string_view
    {
        switch (opcode)
        {
        case OpCode::none:          return "none";
        case OpCode::aconst_null:   return "aconst_null";
        case OpCode::iconst_m1:     return "iconst_m1";
        case OpCode::iconst_0:      return "iconst_0";
        case OpCode::iconst_1:      return "iconst_1";
        case OpCode::iconst_2:      return "iconst_2";
        case OpCode::iconst_3:      return "iconst_3";
        case OpCode::iconst_4:      return "iconst_4";
        case OpCode::iconst_5:      return "iconst_5";
        case OpCode::lconst_0:      return "lconst_0";
        case OpCode::lconst_1:      return "lconst_1";
        case OpCode::fconst_0:      return "fconst_0";
        case OpCode::fconst_1:      return "fconst_1";
        case OpCode::fconst_2:      return "fconst_2";
        case OpCode::dconst_0:      return "dconst_0";
        case OpCode::dconst_1:      return "dconst_1";
        case OpCode::bipush:        return "bipush";
        case OpCode::sipush:        return "sipush";
        case OpCode::ldc:           return "ldc";
        case OpCode::ldc_w:         return "ldc_w";
        case OpCode::ldc2_w:        return "ldc2_w";
        case OpCode::iload_0:       return "iload_0";
        case OpCode::iload_1:       return "iload_1";
        case OpCode::iload_2:       return "iload_2";
        case OpCode::iload_3:       return "iload_3";
        case OpCode::aload_0:       return "aload_0";
        case OpCode::aload_1:       return "aload_1";
        case OpCode::aload_2:       return "aload_2";
        case OpCode::aload_3:       return "aload_3";
        case OpCode::istore_0:      return "istore_0";
        case OpCode::istore_1:      return "istore_1";
        case OpCode::istore_2:      return "istore_2";
        case OpCode::istore_3:      return "istore_3";
        case OpCode::iadd:          return "iadd";
        case OpCode::isub:          return "isub";
        case OpCode::imul:          return "imul";
        case OpCode::idiv:          return "idiv";
        case OpCode::irem:          return "irem";
        case OpCode::ret:           return "return";
        case OpCode::getstatic:     return "getstatic";
        case OpCode::invokevirtual: return "invokevirtual";
        case OpCode::invokespecial: return "invokespecial";
        case OpCode::invokestatic:  return "invokestatic";
        }
        return "unsupported";
    }
}