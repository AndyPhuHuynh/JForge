#pragma once

#include <bit>
#include <istream>

namespace jforge::util
{
    template <typename T>
    auto read_bytes_be(std::istream& stream) -> T
    {
        T t;
        stream.read(reinterpret_cast<char *>(&t), sizeof(T));
        if constexpr (std::endian::native != std::endian::big)
            t = std::byteswap(t); // NOLINT (unreachable-code)
        return t;
    }

    template <typename T>
    auto write_bytes_be(std::ostream& stream, T t) -> void
    {
        if constexpr (std::endian::native != std::endian::big)
            t = std::byteswap(t); // NOLINT (unreachable-code)
        stream.write(reinterpret_cast<char *>(&t), sizeof(T));
    }

    template <std::size_t N>
    std::string formatHex(const uint8_t (&arr)[N]) {
        std::string out;
        out.reserve(N * 2);
        for (auto b : arr) {
            out += std::format("{:02X}", b);
        }
        return out;
    }
}