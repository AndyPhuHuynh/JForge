#pragma once

#include <string>

namespace jforge::builder
{
    struct Fieldref
    {
        std::string className;
        std::string fieldName;
        std::string descriptor;

        Fieldref() = default;
        Fieldref(const std::string_view _className, const std::string_view _fieldName, const std::string_view _descriptor)
            : className(_className), fieldName(_fieldName), descriptor(_descriptor) {}
    };

    struct Methodref
    {
        std::string className;
        std::string methodName;
        std::string descriptor;

        Methodref() = default;
        Methodref(const std::string_view _className, const std::string_view _methodName, const std::string_view _descriptor)
            : className(_className), methodName(_methodName), descriptor(_descriptor) {}
    };

    struct InterfaceMethodref
    {
        std::string className;
        std::string methodName;
        std::string descriptor;

        InterfaceMethodref() = default;
        InterfaceMethodref(const std::string_view _className, const std::string_view _methodName, const std::string_view _descriptor)
            : className(_className), methodName(_methodName), descriptor(_descriptor) {}
    };
}