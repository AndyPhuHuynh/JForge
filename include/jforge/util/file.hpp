#pragma once

#include <bit>
#include <istream>

namespace jforge::util
{
    template <typename T>
    auto read_bytes_le(std::istream& stream) -> T
    {
        T t;
        stream.read(reinterpret_cast<char *>(&t), sizeof(T));
        if constexpr (std::endian::native != std::endian::little)
            t = std::byteswap(t); // NOLINT (unreachable-code)
        return t;
    }

    template <typename T>
    auto read_bytes_be(std::istream& stream) -> T
    {
        T t;
        stream.read(reinterpret_cast<char *>(&t), sizeof(T));
        if constexpr (std::endian::native != std::endian::big)
            t = std::byteswap(t); // NOLINT (unreachable-code)
        return t;
    }
}