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

#include <iostream>
#include <fstream>

#include "jforge/builder/class_builder.hpp"
#include "jforge/builder/method_builder.hpp"
#include "jforge/bytecode/decoder.hpp"
#include "jforge/classfile/parser.hpp"

int main(const int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Provide one arg";
        return 1;
    }
    if (std::string(argv[1]) == "write")
    {
        auto init = jforge::builder::MethodBuilder(
            jforge::access::Method::Public,
            "<init>",
            "()V"
        );

        init.aload0();
        init.invokespecial("java/lang/Object", "<init>", "()V");
        init.ret();

        auto mb = jforge::builder::MethodBuilder(
            jforge::access::Method::Public | jforge::access::Method::Static,
            "main", "([Ljava/lang/String;)V"
        );
        mb.getstatic("java/lang/System", "out", "Ljava/io/PrintStream;");
        mb.ldcString("Hello World!");
        mb.invokevirtual("java/io/PrintStream", "println", "(Ljava/lang/String;)V");
        mb.ret();

        auto cb = jforge::builder::ClassBuilder("Output");
        cb.addMethod(std::move(init));
        cb.addMethod(std::move(mb));

        auto res = cb.emit("./Output.class");
        if (!res)
        {
            std::cerr << "Failed to emit output class: " << res.error();
            return 1;
        }
        return 0;
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
