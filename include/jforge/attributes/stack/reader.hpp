#pragma once

#include <expected>
#include <iosfwd>
#include <string>

#include "jforge/attributes/stack/frame.hpp"

namespace jforge::attributes::stack
{
    auto readVerificationTypeInfo(std::istream& stream) -> std::expected<VerificationTypeInfo, std::string>;
    auto readFrame(std::istream& stream) -> std::expected<StackMapFrame, std::string>;
}
