#pragma once

#include <string>
#include <variant>

namespace jforge
{
    struct LdcString
    {
        std::string value;
    };

    struct ALoad0 {};
    struct ALoad1 {};
    struct ALoad2 {};
    struct ALoad3 {};

    struct Ret {};

    struct GetStatic
    {
        std::string className;
        std::string fieldName;
        std::string descriptor;
    };

    struct InvokeVirtual
    {
        std::string className;
        std::string methodName;
        std::string descriptor;
    };

    struct InvokeSpecial
    {
        std::string className;
        std::string methodName;
        std::string descriptor;
    };

    using Instructions = std::variant<
        LdcString,
        ALoad0,
        ALoad1,
        ALoad2,
        ALoad3,
        GetStatic,
        InvokeVirtual,
        InvokeSpecial,
        Ret
    >;
}