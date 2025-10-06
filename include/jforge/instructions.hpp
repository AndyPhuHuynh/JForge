#pragma once

#include <string>
#include <variant>

namespace jforge
{
    struct LdcString
    {
        std::string value;
    };

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

    using Instructions = std::variant<
        GetStatic,
        LdcString,
        InvokeVirtual
    >;
}