#include <fstream>
#include <iostream>
#include <span>

#include "jforge/bytecode/decoder.hpp"
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
    const auto classfile = jforge::classfile::readClassFile(file);
    if (!classfile)
    {
        std::cerr << "Failed to read class file: " << classfile.error() << std::endl;
        return 1;
    }
    for (const auto& method: classfile->methods)
    {
        // jforge::classfile::printMethod(std::cout, method);
        for (const auto& attr : method.attributes)
        {
            if (classfile->constantPool.getUtf8(attr.nameIndex) == "Code")
            {
                const auto& code = std::get<jforge::attributes::Code>(attr.value);
                jforge::bytecode::printBytecodes(classfile->constantPool, std::span(code.code));
            }
        }
        std::cout << "------------------------------------------\n";
    }
}
