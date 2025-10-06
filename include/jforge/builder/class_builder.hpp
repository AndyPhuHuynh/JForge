#pragma once

#include <filesystem>
#include <vector>

#include "jforge/builder/method_builder.hpp"
#include "jforge/constant_pool/constant_pool.hpp"

namespace jforge::builder
{
    class ClassBuilder
    {
        std::vector<MethodBuilder> m_methods;
    public:
        void addMethod(MethodBuilder method);

        void emit(const std::filesystem::path& output);

        auto generateConstantPool() -> constant_pool::ConstantPool;
    };
}
