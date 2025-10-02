#pragma once

#include <iostream>

namespace jforge::util
{
    struct Indent
    {
        size_t level;
    };

    inline std::ostream& operator<<(std::ostream& os, const Indent& indent)
    {
        for (int i = 0; i < indent.level; i++)
        {
            os << " ";
        }
        return os;
    }
}
