#pragma once

#include <filesystem>
#include <vector>

#include "jforge/builder/method_builder.hpp"
#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::builder
{
    class ClassBuilder
    {
        std::string m_name;
        std::vector<MethodBuilder> m_methods;
    public:
        ClassBuilder(std::string_view name);

        void addMethod(MethodBuilder method);

        std::expected<void, std::string> emit(const std::filesystem::path& output);

        auto generateConstantPool() -> constant_pool::ConstantPool;
    };
}
