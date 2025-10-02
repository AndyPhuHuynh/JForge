#pragma once

#include <iosfwd>

#include "jforge/constant_pool/infos.hpp"

namespace jforge::constant_pool
{
    std::ostream& operator<<(std::ostream& os, const NullInfo& entry);
    std::ostream& operator<<(std::ostream& os, const Utf8Info& entry);
    std::ostream& operator<<(std::ostream& os, const ClassInfo& entry);
    std::ostream& operator<<(std::ostream& os, const StringInfo& entry);
    std::ostream& operator<<(std::ostream& os, const FieldrefInfo& entry);
    std::ostream& operator<<(std::ostream& os, const MethodrefInfo& entry);
    std::ostream& operator<<(std::ostream& os, const InterfaceMethodrefInfo& entry);
    std::ostream& operator<<(std::ostream& os, const NameAndTypeInfo& entry);

    std::ostream& operator<<(std::ostream& os, const PoolEntry& entry);
}