#pragma once

#include <bit>
#include <cstring>
#include <istream>

namespace jforge::util
{
    template <typename T>
    auto read_bytes_be(std::istream& stream) -> T
    {
        char buffer[sizeof(T)];
        stream.read(buffer, sizeof(T));
        if constexpr (std::endian::native != std::endian::big)
            std::reverse(buffer, buffer + sizeof(T)); // NOLINT (unreachable-code)
        return std::bit_cast<T>(buffer);
    }

    template <typename T>
    auto write_bytes_be(std::ostream& stream, T t) -> void
    {
        char buffer[sizeof(T)];
        std::memcpy(buffer, &t, sizeof(T));
        if constexpr (std::endian::native != std::endian::big)
            std::reverse(buffer, buffer + sizeof(T)); // NOLINT (unreachable-code)
        stream.write(buffer, sizeof(T));
    }

    template <std::size_t N>
    std::string formatHex(const char (&arr)[N]) {
        std::string out;
        out.reserve(N * 2);
        for (auto b : arr) {
            out += std::format("{:02X}", b);
        }
        return out;
    }
}