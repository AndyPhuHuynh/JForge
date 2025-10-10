#pragma once

#include <cstdint>
#include <variant>
#include <vector>

#include "verification_type.hpp"

namespace jforge::attributes::stack
{
    enum class FrameType
    {
        SameFrame,
        SameLocals1StackItemFrame,
        SameLocals1StackItemFrameExtended,
        ChopFrame,
        SameFrameExtended,
        AppendFrame,
        FullFrame,
        Reserved
    };

    struct SameFrame {};

    struct SameLocals1StackItemFrame
    {
        VerificationTypeInfo type;
    };

    struct SameLocals1StackItemFrameExtended
    {
        uint16_t offsetDelta;
        VerificationTypeInfo type;
    };

    struct ChopFrame
    {
        uint16_t offsetDelta;
    };

    struct SameFrameExtended
    {
        uint16_t offsetDelta;
    };

    struct AppendFrame
    {
        uint16_t offsetDelta;
        std::vector<VerificationTypeInfo> locals;
    };

    struct FullFrame
    {
        uint16_t offsetDelta;
        std::vector<VerificationTypeInfo> locals;
        std::vector<VerificationTypeInfo> stack;
    };

    using FrameVariant = std::variant<
        SameFrame,
        SameLocals1StackItemFrame,
        SameLocals1StackItemFrameExtended,
        ChopFrame,
        SameFrameExtended,
        AppendFrame,
        FullFrame
    >;

    struct StackMapFrame
    {
        uint8_t frameType;
        FrameVariant data;
    };

    inline auto frameTypeFromNum(const uint8_t num) -> FrameType
    {
        if (num <= 63)  return FrameType::SameFrame;
        if (num <= 127) return FrameType::SameLocals1StackItemFrame;
        if (num <= 246) return FrameType::Reserved;
        if (num == 247) return FrameType::SameLocals1StackItemFrameExtended;
        if (num <= 250) return FrameType::ChopFrame;
        if (num == 251) return FrameType::SameFrameExtended;
        if (num <= 254) return FrameType::AppendFrame;
        return FrameType::FullFrame;
    }
}
