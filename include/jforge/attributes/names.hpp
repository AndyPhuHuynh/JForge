#pragma once

#include <string_view>

namespace jforge::attributes
{
    constexpr std::string_view CodeID            = "Code";
    constexpr std::string_view StackMapTableID   = "StackMapTable";
    constexpr std::string_view SourceFileID      = "SourceFile";
    constexpr std::string_view LineNumberTableId = "LineNumberTable";
}