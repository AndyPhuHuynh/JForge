#pragma once

#include <cstdint>

namespace jforge::bytecode
{
    struct GetStatic
    {
        uint16_t fieldrefIndex;
    };
}
