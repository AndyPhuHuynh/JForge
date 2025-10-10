#pragma once

#include <cstdint>
#include <expected>
#include <format>

namespace jforge::attributes::stack
{
    enum class VerificationType : uint8_t
    {
        Top                     = 0,
        Integer                 = 1,
        Float                   = 2,
        Double                  = 3,
        Long                    = 4,
        Null                    = 5,
        UninitializedThis       = 6,
        Object                  = 7,
        UninitializedVariable   = 8,
    };

    struct VerificationTypeInfo
    {
        VerificationType tag;
        uint16_t data;
    };

    inline auto verificationTypeFromNum(uint8_t num) -> std::expected<VerificationType, std::string>
    {
        if (num == 0 || num > 8)
            return std::unexpected(std::format("Invalid verification type tag: {}", num));
        return static_cast<VerificationType>(num);
    }
}
