#include <iostream>
#include <fstream>

#include "jforge/builder/class_builder.hpp"
#include "jforge/builder/method_builder.hpp"
#include "jforge/bytecode/decoder.hpp"
#include "jforge/classfile/parser.hpp"

void read(const std::filesystem::path& path)
{
    auto file = std::ifstream(path, std::ios::binary);
    const auto classfile = jforge::classfile::readClassFile(file);
    if (!classfile)
    {
        std::cerr << "Failed to read class file: " << classfile.error() << std::endl;
        return;
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

        auto printInt = jforge::builder::MethodBuilder(
            jforge::access::Method::Public | jforge::access::Method::Static,
            "printInt",
            "()V"
        );
        printInt.getstatic("java/lang/System", "out", "Ljava/io/PrintStream;");
        printInt.iconst_1();
        printInt.iconst_2();
        printInt.iadd();
        printInt.invokevirtual("java/io/PrintStream", "println", "(I)V");
        printInt.ret();

        auto main = jforge::builder::MethodBuilder(
            jforge::access::Method::Public | jforge::access::Method::Static,
            "main",
            "([Ljava/lang/String;)V"
        );
        main.getstatic("java/lang/System", "out", "Ljava/io/PrintStream;");
        main.ldcString("Hello World!");
        main.invokevirtual("java/io/PrintStream", "println", "(Ljava/lang/String;)V");


        main.invokestatic("Output", "printInt", "()V");

        main.ret();



        auto cb = jforge::builder::ClassBuilder("Output");
        cb.addMethod(std::move(init));
        cb.addMethod(std::move(printInt));
        cb.addMethod(std::move(main));

        if (auto res = cb.emit("./Output.class"); !res)
        {
            std::cerr << "Failed to emit output class: " << res.error();
            return 1;
        }
        return 0;
    }
    else
    {
        read(argv[1]);
    }
}
