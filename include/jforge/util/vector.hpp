#pragma once

#include <cstdint>
#include <vector>

namespace jforge::util
{
    template <typename T>
    auto push_back_be(std::vector<uint8_t>& vec, T t) -> void
    {
        if constexpr (std::endian::native != std::endian::big)
            t = std::byteswap(t); // NOLINT
        const auto bytes = reinterpret_cast<uint8_t *>(&t);
        vec.insert(vec.end(), bytes, bytes + sizeof(T));
    }
}