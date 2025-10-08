#pragma once

#include <cstdint>
#include <vector>

namespace jforge::util
{
    template <typename T>
    auto push_back_be(std::vector<uint8_t>& vec, T t) -> void
    {
        uint8_t buffer[sizeof(T)];
        memcpy(buffer, &t, sizeof(T));
        if constexpr (std::endian::native != std::endian::big)
            std::reverse(buffer, buffer + sizeof(T)); // NOLINT
        vec.insert(vec.end(), buffer, buffer + sizeof(T));
    }
}