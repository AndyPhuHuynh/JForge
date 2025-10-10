#pragma once

#include <cstdint>
#include <string>

namespace jforge::bytecode
{
    class Label
    {
    public:
        using Id = std::uint64_t;
    private:
        Id m_id = 0;
        std::string m_name;

        auto generateId() -> void;
    public:

        Label();
        explicit Label(std::string_view name);

        auto getId() const -> uint64_t;
        auto getName() const -> std::string_view;

        auto operator==(const Label& other) const -> bool = default;
    };
}

template <>
struct std::hash<jforge::bytecode::Label>
{
    std::size_t operator()(const jforge::bytecode::Label& label) const noexcept
    {
        return std::hash<uint64_t>()(label.getId());
    }
};
