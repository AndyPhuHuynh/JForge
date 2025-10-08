#pragma once

#include <cstdint>

namespace jforge::bytecode
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

        iload         = 0x15,
        lload         = 0x16,
        fload         = 0x17,
        dload         = 0x18,
        aload         = 0x19,

        iload_0       = 0x1a,
        iload_1       = 0x1b,
        iload_2       = 0x1c,
        iload_3       = 0x1d,

        lload_0       = 0x1e,
        lload_1       = 0x1f,
        lload_2       = 0x20,
        lload_3       = 0x21,

        fload_0       = 0x22,
        fload_1       = 0x23,
        fload_2       = 0x24,
        fload_3       = 0x25,

        dload_0       = 0x26,
        dload_1       = 0x27,
        dload_2       = 0x28,
        dload_3       = 0x29,

        aload_0       = 0x2a,
        aload_1       = 0x2b,
        aload_2       = 0x2c,
        aload_3       = 0x2d,

        iaload        = 0x2e,
        laload        = 0x2f,
        faload        = 0x30,
        daload        = 0x31,
        aaload        = 0x32,
        baload        = 0x33,
        caload        = 0x34,
        saload        = 0x35,

        istore        = 0x36,
        lstore        = 0x37,
        fstore        = 0x38,
        dstore        = 0x39,
        astore        = 0x3a,

        istore_0      = 0x3b,
        istore_1      = 0x3c,
        istore_2      = 0x3d,
        istore_3      = 0x3e,

        lstore_0      = 0x3f,
        lstore_1      = 0x40,
        lstore_2      = 0x41,
        lstore_3      = 0x42,

        fstore_0      = 0x43,
        fstore_1      = 0x44,
        fstore_2      = 0x45,
        fstore_3      = 0x46,

        dstore_0      = 0x47,
        dstore_1      = 0x48,
        dstore_2      = 0x49,
        dstore_3      = 0x4a,

        astore_0      = 0x4b,
        astore_1      = 0x4c,
        astore_2      = 0x4d,
        astore_3      = 0x4e,

        iastore       = 0x4f,
        lastore       = 0x50,
        fastore       = 0x51,
        dastore       = 0x52,
        aastore       = 0x53,
        bastore       = 0x54,
        castore       = 0x55,
        sastore       = 0x56,

        pop           = 0x57,
        pop2          = 0x58,
        dup           = 0x59,
        dup_x1        = 0x5a,
        dup_x2        = 0x5b,
        dup2          = 0x5c,
        dup2_x1       = 0x5d,
        dup2_x2       = 0x5e,
        swap          = 0x5f,

        iadd          = 0x60,
        ladd          = 0x61,
        fadd          = 0x62,
        dadd          = 0x63,

        isub          = 0x64,
        lsub          = 0x65,
        fsub          = 0x66,
        dsub          = 0x67,

        imul          = 0x68,
        lmul          = 0x69,
        fmul          = 0x6a,
        dmul          = 0x6b,

        idiv          = 0x6c,
        ldiv          = 0x6d,
        fdiv          = 0x6e,
        ddiv          = 0x6f,

        irem          = 0x70,
        lrem          = 0x71,
        frem          = 0x72,
        drem          = 0x73,

        ineg          = 0x74,
        lneg          = 0x75,
        fneg          = 0x76,
        dneg          = 0x77,

        ishl          = 0x78,
        lshl          = 0x79,
        ishr          = 0x7a,
        lshr          = 0x7b,
        iushr         = 0x7c,
        lushr         = 0x7d,

        iand          = 0x7e,
        land          = 0x7f,
        ior           = 0x80,
        lor           = 0x81,
        ixor          = 0x82,
        lxor          = 0x83,

        iinc          = 0x84,

        i2l           = 0x85,
        i2f           = 0x86,
        i2d           = 0x87,

        l2i           = 0x88,
        l2f           = 0x89,
        l2d           = 0x8a,

        f2i           = 0x8b,
        f2l           = 0x8c,
        f2d           = 0x8d,

        d2i           = 0x8e,
        d2l           = 0x8f,
        d2f           = 0x90,

        i2b           = 0x91,
        i2c           = 0x92,
        i2s           = 0x93,

        lcmp          = 0x94,
        fcmpl         = 0x95,
        fcmpg         = 0x96,
        dcmpl         = 0x97,
        dcmpg         = 0x98,

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

        case 0x15: return OpCode::iload;
        case 0x16: return OpCode::lload;
        case 0x17: return OpCode::fload;
        case 0x18: return OpCode::dload;
        case 0x19: return OpCode::aload;

        case 0x1a: return OpCode::iload_0;
        case 0x1b: return OpCode::iload_1;
        case 0x1c: return OpCode::iload_2;
        case 0x1d: return OpCode::iload_3;

        case 0x1e: return OpCode::lload_0;
        case 0x1f: return OpCode::lload_1;
        case 0x20: return OpCode::lload_2;
        case 0x21: return OpCode::lload_3;

        case 0x22: return OpCode::fload_0;
        case 0x23: return OpCode::fload_1;
        case 0x24: return OpCode::fload_2;
        case 0x25: return OpCode::fload_3;

        case 0x26: return OpCode::dload_0;
        case 0x27: return OpCode::dload_1;
        case 0x28: return OpCode::dload_2;
        case 0x29: return OpCode::dload_3;

        case 0x2a: return OpCode::aload_0;
        case 0x2b: return OpCode::aload_1;
        case 0x2c: return OpCode::aload_2;
        case 0x2d: return OpCode::aload_3;

        case 0x2e: return OpCode::iaload;
        case 0x2f: return OpCode::laload;
        case 0x30: return OpCode::faload;
        case 0x31: return OpCode::daload;
        case 0x32: return OpCode::aaload;
        case 0x33: return OpCode::baload;
        case 0x34: return OpCode::caload;
        case 0x35: return OpCode::saload;

        case 0x36: return OpCode::istore;
        case 0x37: return OpCode::lstore;
        case 0x38: return OpCode::fstore;
        case 0x39: return OpCode::dstore;
        case 0x3a: return OpCode::astore;

        case 0x3b: return OpCode::istore_0;
        case 0x3c: return OpCode::istore_1;
        case 0x3d: return OpCode::istore_2;
        case 0x3e: return OpCode::istore_3;

        case 0x3f: return OpCode::lstore_0;
        case 0x40: return OpCode::lstore_1;
        case 0x41: return OpCode::lstore_2;
        case 0x42: return OpCode::lstore_3;

        case 0x43: return OpCode::fstore_0;
        case 0x44: return OpCode::fstore_1;
        case 0x45: return OpCode::fstore_2;
        case 0x46: return OpCode::fstore_3;

        case 0x47: return OpCode::dstore_0;
        case 0x48: return OpCode::dstore_1;
        case 0x49: return OpCode::dstore_2;
        case 0x4a: return OpCode::dstore_3;

        case 0x4b: return OpCode::astore_0;
        case 0x4c: return OpCode::astore_1;
        case 0x4d: return OpCode::astore_2;
        case 0x4e: return OpCode::astore_3;

        case 0x4f: return OpCode::iastore;
        case 0x50: return OpCode::lastore;
        case 0x51: return OpCode::fastore;
        case 0x52: return OpCode::dastore;
        case 0x53: return OpCode::aastore;
        case 0x54: return OpCode::bastore;
        case 0x55: return OpCode::castore;
        case 0x56: return OpCode::sastore;

        case 0x57: return OpCode::pop;
        case 0x58: return OpCode::pop2;
        case 0x59: return OpCode::dup;
        case 0x5a: return OpCode::dup_x1;
        case 0x5b: return OpCode::dup_x2;
        case 0x5c: return OpCode::dup2;
        case 0x5d: return OpCode::dup2_x1;
        case 0x5e: return OpCode::dup2_x2;
        case 0x5f: return OpCode::swap;

        case 0x60: return OpCode::iadd;
        case 0x61: return OpCode::ladd;
        case 0x62: return OpCode::fadd;
        case 0x63: return OpCode::dadd;

        case 0x64: return OpCode::isub;
        case 0x65: return OpCode::lsub;
        case 0x66: return OpCode::fsub;
        case 0x67: return OpCode::dsub;

        case 0x68: return OpCode::imul;
        case 0x69: return OpCode::lmul;
        case 0x6a: return OpCode::fmul;
        case 0x6b: return OpCode::dmul;

        case 0x6c: return OpCode::idiv;
        case 0x6d: return OpCode::ldiv;
        case 0x6e: return OpCode::fdiv;
        case 0x6f: return OpCode::ddiv;

        case 0x70: return OpCode::irem;
        case 0x71: return OpCode::lrem;
        case 0x72: return OpCode::frem;
        case 0x73: return OpCode::drem;

        case 0x74: return OpCode::ineg;
        case 0x75: return OpCode::lneg;
        case 0x76: return OpCode::fneg;
        case 0x77: return OpCode::dneg;

        case 0x78: return OpCode::ishl;
        case 0x79: return OpCode::lshl;
        case 0x7a: return OpCode::ishr;
        case 0x7b: return OpCode::lshr;
        case 0x7c: return OpCode::iushr;
        case 0x7d: return OpCode::lushr;

        case 0x7e: return OpCode::iand;
        case 0x7f: return OpCode::land;
        case 0x80: return OpCode::ior;
        case 0x81: return OpCode::lor;
        case 0x82: return OpCode::ixor;
        case 0x83: return OpCode::lxor;

        case 0x84: return OpCode::iinc;

        case 0x85: return OpCode::i2l;
        case 0x86: return OpCode::i2f;
        case 0x87: return OpCode::i2d;

        case 0x88: return OpCode::l2i;
        case 0x89: return OpCode::l2f;
        case 0x8a: return OpCode::l2d;

        case 0x8b: return OpCode::f2i;
        case 0x8c: return OpCode::f2l;
        case 0x8d: return OpCode::f2d;

        case 0x8e: return OpCode::d2i;
        case 0x8f: return OpCode::d2l;
        case 0x90: return OpCode::d2f;

        case 0x91: return OpCode::i2b;
        case 0x92: return OpCode::i2c;
        case 0x93: return OpCode::i2s;

        case 0x94: return OpCode::lcmp;
        case 0x95: return OpCode::fcmpl;
        case 0x96: return OpCode::fcmpg;
        case 0x97: return OpCode::dcmpl;
        case 0x98: return OpCode::dcmpg;

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

        case OpCode::iload:         return "iload";
        case OpCode::lload:         return "lload";
        case OpCode::fload:         return "fload";
        case OpCode::dload:         return "dload";
        case OpCode::aload:         return "aload";

        case OpCode::iload_0:       return "iload_0";
        case OpCode::iload_1:       return "iload_1";
        case OpCode::iload_2:       return "iload_2";
        case OpCode::iload_3:       return "iload_3";

        case OpCode::lload_0:       return "lload_0";
        case OpCode::lload_1:       return "lload_1";
        case OpCode::lload_2:       return "lload_2";
        case OpCode::lload_3:       return "lload_3";

        case OpCode::fload_0:       return "fload_0";
        case OpCode::fload_1:       return "fload_1";
        case OpCode::fload_2:       return "fload_2";
        case OpCode::fload_3:       return "fload_3";

        case OpCode::dload_0:       return "dload_0";
        case OpCode::dload_1:       return "dload_1";
        case OpCode::dload_2:       return "dload_2";
        case OpCode::dload_3:       return "dload_3";

        case OpCode::aload_0:       return "aload_0";
        case OpCode::aload_1:       return "aload_1";
        case OpCode::aload_2:       return "aload_2";
        case OpCode::aload_3:       return "aload_3";

        case OpCode::iaload:        return "iaload";
        case OpCode::laload:        return "laload";
        case OpCode::faload:        return "faload";
        case OpCode::daload:        return "daload";
        case OpCode::aaload:        return "aaload";
        case OpCode::baload:        return "baload";
        case OpCode::caload:        return "caload";
        case OpCode::saload:        return "saload";

        case OpCode::istore:        return "istore";
        case OpCode::lstore:        return "lstore";
        case OpCode::fstore:        return "fstore";
        case OpCode::dstore:        return "dstore";
        case OpCode::astore:        return "astore";

        case OpCode::istore_0:      return "istore_0";
        case OpCode::istore_1:      return "istore_1";
        case OpCode::istore_2:      return "istore_2";
        case OpCode::istore_3:      return "istore_3";

        case OpCode::lstore_0:      return "lstore_0";
        case OpCode::lstore_1:      return "lstore_1";
        case OpCode::lstore_2:      return "lstore_2";
        case OpCode::lstore_3:      return "lstore_3";

        case OpCode::fstore_0:      return "fstore_0";
        case OpCode::fstore_1:      return "fstore_1";
        case OpCode::fstore_2:      return "fstore_2";
        case OpCode::fstore_3:      return "fstore_3";

        case OpCode::dstore_0:      return "dstore_0";
        case OpCode::dstore_1:      return "dstore_1";
        case OpCode::dstore_2:      return "dstore_2";
        case OpCode::dstore_3:      return "dstore_3";

        case OpCode::astore_0:      return "astore_0";
        case OpCode::astore_1:      return "astore_1";
        case OpCode::astore_2:      return "astore_2";
        case OpCode::astore_3:      return "astore_3";

        case OpCode::iastore:       return "iastore";
        case OpCode::lastore:       return "lastore";
        case OpCode::fastore:       return "fastore";
        case OpCode::dastore:       return "dastore";
        case OpCode::aastore:       return "aastore";
        case OpCode::bastore:       return "bastore";
        case OpCode::castore:       return "castore";
        case OpCode::sastore:       return "sastore";

        case OpCode::pop:           return "pop";
        case OpCode::pop2:          return "pop2";
        case OpCode::dup:           return "dup";
        case OpCode::dup_x1:        return "dup_x1";
        case OpCode::dup_x2:        return "dup_x2";
        case OpCode::dup2:          return "dup2";
        case OpCode::dup2_x1:       return "dup2_x1";
        case OpCode::dup2_x2:       return "dup2_x2";
        case OpCode::swap:          return "swap";

        case OpCode::iadd:          return "iadd";
        case OpCode::ladd:          return "ladd";
        case OpCode::fadd:          return "fadd";
        case OpCode::dadd:          return "dadd";

        case OpCode::isub:          return "isub";
        case OpCode::lsub:          return "lsub";
        case OpCode::fsub:          return "fsub";
        case OpCode::dsub:          return "dsub";

        case OpCode::imul:          return "imul";
        case OpCode::lmul:          return "lmul";
        case OpCode::fmul:          return "fmul";
        case OpCode::dmul:          return "dmul";

        case OpCode::idiv:          return "idiv";
        case OpCode::ldiv:          return "ldiv";
        case OpCode::fdiv:          return "fdiv";
        case OpCode::ddiv:          return "ddiv";

        case OpCode::irem:          return "irem";
        case OpCode::lrem:          return "lrem";
        case OpCode::frem:          return "frem";
        case OpCode::drem:          return "drem";

        case OpCode::ineg:          return "ineg";
        case OpCode::lneg:          return "lneg";
        case OpCode::fneg:          return "fneg";
        case OpCode::dneg:          return "dneg";

        case OpCode::ishl:          return "ishl";
        case OpCode::lshl:          return "lshl";
        case OpCode::ishr:          return "ishr";
        case OpCode::lshr:          return "lshr";
        case OpCode::iushr:         return "iushr";
        case OpCode::lushr:         return "lushr";

        case OpCode::iand:          return "iand";
        case OpCode::land:          return "land";
        case OpCode::ior:           return "ior";
        case OpCode::lor:           return "lor";
        case OpCode::ixor:          return "ixor";
        case OpCode::lxor:          return "lxor";

        case OpCode::iinc:          return "iinc";

        case OpCode::i2l:           return "i2l";
        case OpCode::i2f:           return "i2f";
        case OpCode::i2d:           return "i2d";

        case OpCode::l2i:           return "l2i";
        case OpCode::l2f:           return "l2f";
        case OpCode::l2d:           return "l2d";

        case OpCode::f2i:           return "f2i";
        case OpCode::f2l:           return "f2l";
        case OpCode::f2d:           return "f2d";

        case OpCode::d2i:           return "d2i";
        case OpCode::d2l:           return "d2l";
        case OpCode::d2f:           return "d2f";

        case OpCode::i2b:           return "i2b";
        case OpCode::i2c:           return "i2c";
        case OpCode::i2s:           return "i2s";

        case OpCode::lcmp:          return "lcmp";
        case OpCode::fcmpl:         return "fcmpl";
        case OpCode::fcmpg:         return "fcmpg";
        case OpCode::dcmpl:         return "dcmpl";
        case OpCode::dcmpg:         return "dcmpg";

        case OpCode::ret:           return "return";
        case OpCode::getstatic:     return "getstatic";
        case OpCode::invokevirtual: return "invokevirtual";
        case OpCode::invokespecial: return "invokespecial";
        case OpCode::invokestatic:  return "invokestatic";
        }
        return "unsupported";
    }
}