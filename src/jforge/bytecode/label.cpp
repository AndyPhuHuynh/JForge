#include "jforge/bytecode/label.hpp"

#include <random>

namespace jforge::bytecode
{
    auto Label::generateId() -> void
    {
        std::mt19937_64 rng(std::random_device{}());
        std::uniform_int_distribution distribution {
            std::numeric_limits<uint64_t>::min(),
            std::numeric_limits<uint64_t>::max()
        };
        m_id = distribution(rng);
    }

    Label::Label()
    {
        generateId();
    }

    Label::Label(const std::string_view name)
        : m_name(name)
    {
        generateId();
    }

    auto Label::getId() const -> uint64_t
    {
        return m_id;
    }

    auto Label::getName() const -> std::string_view
    {
        return m_name;
    }
}
