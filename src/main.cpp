#include <fstream>
#include <iostream>
#include <ranges>

#include "jforge/classfile/parser.hpp"
#include "jforge/classfile/printer.hpp"
#include "jforge/constant_pool/parser.hpp"
#include "jforge/constant_pool/printer.hpp"
#include "jforge/util/file.hpp"

int main(const int argc, const char *argv[])
{
    if (argc < 1)
    {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }
    auto file = std::ifstream(argv[1], std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    uint8_t magic[4];
    file.read(reinterpret_cast<char *>(magic), std::size(magic));
    std::cout << "Magic: " << "0x" << std::hex;
    for (const auto i : magic)
    {
        std::cout << +i;
    }
    std::cout << std::dec << "\n";

    const auto minorVersion = jforge::util::read_bytes_be<uint16_t>(file);
    const auto majorVersion = jforge::util::read_bytes_be<uint16_t>(file);
    std::cout << "Minor version: " << minorVersion << "\n";
    std::cout << "Major version: " << majorVersion << "\n";

    const auto constantPoolCount = jforge::util::read_bytes_be<uint16_t>(file);
    std::cout << "Constant pool count: " << constantPoolCount << "\n";

    std::cout << "\n";
    auto pool = jforge::constant_pool::readConstantPool(file, constantPoolCount);
    if (!pool)
    {
        std::cerr << "Unable to read constant pool: " << pool.error() << "\n";
        return 1;
    }
    for (const auto& [i, entry] : std::views::enumerate(pool->allEntries()))
    {
        std::cout << "Index " << i << ": ";
        std::cout << entry << "\n";
    }

    const auto accessFlags = jforge::util::read_bytes_be<uint16_t>(file);
    std::cout << "Access flags: 0x" << std::hex << accessFlags << std::dec << "\n";

    const auto thisParam = jforge::util::read_bytes_be<uint16_t>(file);
    const auto super     = jforge::util::read_bytes_be<uint16_t>(file);
    std::cout << "This: " << thisParam << "\n";
    std::cout << "Super: " << super << "\n";

    const auto interfacesCount = jforge::util::read_bytes_be<uint16_t>(file);
    std::cout << "Interfaces count: " << interfacesCount << "\n";
    if (interfacesCount > 0)
    {
        std::cerr << "Interfaces not yet supported\n";
        std::terminate();
    }

    const auto fieldsCount = jforge::util::read_bytes_be<uint16_t>(file);
    std::cout << "Field count: " << fieldsCount << "\n";
    if (fieldsCount > 0)
    {
        std::cerr << "Fields not yet supported\n";
        std::terminate();
    }

    const auto methodCount = jforge::util::read_bytes_be<uint16_t>(file);
    std::cout << "Method count: " << methodCount << "\n";
    std::cout << "\n";

    std::vector<jforge::classfile::MethodInfo> methods;
    methods.reserve(methodCount);
    for (int i = 0; i < methodCount; i++)
    {
        std::cout << "Method index " << i << ":\n";
        auto method = jforge::classfile::readMethodInfo(file, *pool);
        if (!method)
        {
            std::cerr << "Unable to read method " << method.error() << "\n";
            return 1;
        }
        printMethod(std::cout, *method);
        methods.emplace_back(std::move(*method));
        std::cout << "\n";
    }
    return 0;
}
