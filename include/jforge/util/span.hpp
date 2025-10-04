#pragma once

#include <bit>
#include <cstdint>
#include <cstring>
#include <iostream>

namespace jforge::util
{
    class SpanReader
    {
        size_t m_pos = 0;
        std::span<const uint8_t> m_bytes;
    public:
        explicit SpanReader(const std::span<const uint8_t> bytes) : m_bytes(bytes) {}

        [[nodiscard]] auto can_read(const size_t amount) const -> bool
        {
            return m_pos + amount <= m_bytes.size();
        }

        [[nodiscard]] auto position() const -> size_t { return m_pos; }

        template <typename T>
        auto read_bytes_le() -> T
        {
            T t;
            std::memcpy(&t, m_bytes.data() + m_pos, sizeof(T));
            if constexpr (std::endian::native != std::endian::little)
                t = std::byteswap(t); // NOLINT (unreachable-code)
            m_pos += sizeof(T);
            return t;
        }

        template <typename T>
        auto read_bytes_be() -> T
        {
            T t;
            std::memcpy(&t, m_bytes.data() + m_pos, sizeof(T));
            if constexpr (std::endian::native != std::endian::big)
                t = std::byteswap(t); // NOLINT (unreachable-code)
            m_pos += sizeof(T);
            return t;
        }
    };
}
