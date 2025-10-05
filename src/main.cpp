// #include <fstream>
// #include <iostream>
// #include <span>
//
// #include "jforge/bytecode/decoder.hpp"
// #include "jforge/classfile/parser.hpp"
// #include "jforge/classfile/printer.hpp"
// #include "jforge/constant_pool/parser.hpp"
// #include "jforge/constant_pool/printer.hpp"
// #include "jforge/util/file.hpp"

#include "jforge/builder/class_builder.hpp"
#include "jforge/builder/method_builder.hpp"

int main(const int argc, const char *argv[])
{
    // if (argc < 1)
    // {
    //     std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
    //     return 1;
    // }
    // auto file = std::ifstream(argv[1], std::ios::binary);
    // const auto classfile = jforge::classfile::readClassFile(file);
    // if (!classfile)
    // {
    //     std::cerr << "Failed to read class file: " << classfile.error() << std::endl;
    //     return 1;
    // }
    // for (const auto& method: classfile->methods)
    // {
    //     for (const auto& attr : method.attributes)
    //     {
    //         if (classfile->constantPool.getUtf8(attr.nameIndex) == "Code")
    //         {
    //             const auto& code = std::get<jforge::attributes::Code>(attr.value);
    //             jforge::bytecode::printBytecodes(classfile->constantPool, std::span(code.code));
    //         }
    //     }
    //     std::cout << "------------------------------------------\n";
    // }

    auto mb = jforge::builder::MethodBuilder("name", "descriptor");
    mb.getstatic("java/lang/System", "out", "Ljava/io/PrintStream");
    mb.ldcString("Hello World!");
    mb.invokevirtual("java/io/PrintStream", "println", "(Ljava/lang/string;)V");

    auto cb = jforge::builder::ClassBuilder();
    cb.methods.push_back(std::move(mb));

    cb.emit();
}
