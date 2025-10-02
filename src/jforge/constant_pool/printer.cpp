#include "jforge/constant_pool/printer.hpp"

#include <format>
#include <iostream>

std::ostream& jforge::constant_pool::operator<<(std::ostream& os, const NullInfo& entry)
{
    os << "NullInfo";
    return os;
}

std::ostream& jforge::constant_pool::operator<<(std::ostream& os, const Utf8Info& entry)
{
    os << std::format("Utf8Info: Length={}, Bytes={}", entry.length, entry.bytes);
    return os;
}

std::ostream& jforge::constant_pool::operator<<(std::ostream& os, const ClassInfo& entry)
{
    os << std::format("ClassInfo: NameIndex={}", entry.nameIndex);
    return os;
}

std::ostream& jforge::constant_pool::operator<<(std::ostream& os, const StringInfo& entry)
{
    os << std::format("StringInfo: StringIndex={}", entry.stringIndex);
    return os;
}

std::ostream& jforge::constant_pool::operator<<(std::ostream& os, const FieldrefInfo& entry)
{
    os << std::format("FieldrefInfo: ClassIndex={}, NameAndTypeIndex={}", entry.classIndex, entry.nameAndTypeIndex);
    return os;
}

std::ostream& jforge::constant_pool::operator<<(std::ostream& os, const MethodrefInfo& entry)
{
    os << std::format("MethodrefInfo: ClassIndex={}, NameAndTypeIndex={}", entry.classIndex, entry.nameAndTypeIndex);
    return os;
}

std::ostream& jforge::constant_pool::operator<<(std::ostream& os, const InterfaceMethodrefInfo& entry)
{
    os << std::format("InterfaceMethodrefInfo: ClassIndex={}, NameAndTypeIndex={}", entry.classIndex, entry.nameAndTypeIndex);
    return os;
}

std::ostream& jforge::constant_pool::operator<<(std::ostream& os, const NameAndTypeInfo& entry)
{
    os << std::format("NameAndTypeInfo: NameIndex={}, DescriptorIndex={}", entry.nameIndex, entry.descriptorIndex);
    return os;
}

std::ostream& jforge::constant_pool::operator<<(std::ostream& os, const PoolEntry& entry)
{
    std::visit([&os]<typename T>(const T& e) {
        os << e;
    } , entry);
    return os;
}
