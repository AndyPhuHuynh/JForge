#pragma once

#include <cstdint>
#include <string_view>

namespace jforge::constant_pool
{
    [[nodiscard]] auto hashUtf8(std::string_view utf8) -> uint64_t;
    [[nodiscard]] auto hashClass(std::string_view className) -> uint64_t;
    [[nodiscard]] auto hashString(std::string_view string) -> uint64_t;
    [[nodiscard]] auto hashFieldref(std::string_view className, std::string_view fieldName, std::string_view descriptor) -> uint64_t;
    [[nodiscard]] auto hashMethodref(std::string_view className, std::string_view fieldName, std::string_view descriptor) -> uint64_t;
    [[nodiscard]] auto hashInterfaceMethodref(std::string_view className, std::string_view fieldName, std::string_view descriptor) -> uint64_t;
    [[nodiscard]] auto hashNameAndType(std::string_view name, std::string_view type) -> uint64_t;
}
