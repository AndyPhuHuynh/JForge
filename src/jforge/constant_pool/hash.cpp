#include "jforge/constant_pool/hash.hpp"

static void hashCombine(uint64_t& seed, const size_t value) {
    seed ^= value + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
}

auto jforge::constant_pool::hashUtf8(const std::string_view utf8) -> uint64_t
{
    return std::hash<std::string_view>{}(utf8);
}

auto jforge::constant_pool::hashClass(const std::string_view className) -> uint64_t
{
    return std::hash<std::string_view>{}(className);
}

auto jforge::constant_pool::hashString(const std::string_view string) -> uint64_t
{
    return std::hash<std::string_view>{}(string);
}

auto jforge::constant_pool::hashFieldref(
    const std::string_view className,
    const std::string_view fieldName,
    const std::string_view descriptor) -> uint64_t
{
    uint64_t h = hashString(className);
    hashCombine(h, hashString(fieldName)),
    hashCombine(h, hashString(descriptor));
    return h;
}

auto jforge::constant_pool::hashMethodref(
    const std::string_view className,
    const std::string_view fieldName,
    const std::string_view descriptor) -> uint64_t
{
    uint64_t h = hashString(className);
    hashCombine(h, hashString(fieldName)),
    hashCombine(h, hashString(descriptor));
    return h;
}

auto jforge::constant_pool::hashInterfaceMethodref(
    const std::string_view className,
    const std::string_view fieldName,
    const std::string_view descriptor) -> uint64_t
{
    uint64_t h = hashString(className);
    hashCombine(h, hashString(fieldName)),
    hashCombine(h, hashString(descriptor));
    return h;
}

auto jforge::constant_pool::hashNameAndType(const std::string_view name, const std::string_view type) -> uint64_t
{
    uint64_t h = hashString(name);
    hashCombine(h, hashString(type));
    return h;
}
