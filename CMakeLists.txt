cmake_minimum_required(VERSION 3.5)
project(JForge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_FILES
        include/jforge/access/flags.hpp

        include/jforge/attributes/attributes.hpp
        include/jforge/attributes/printer.hpp
        include/jforge/attributes/parser.hpp

        include/jforge/builder/class_builder.hpp
        include/jforge/builder/method_builder.hpp

        include/jforge/bytecode/decoder.hpp

        include/jforge/classfile/classfile.hpp
        include/jforge/classfile/method.hpp
        include/jforge/classfile/parser.hpp
        include/jforge/classfile/printer.hpp

        include/jforge/constant_pool/constant_pool.hpp
        include/jforge/constant_pool/hash.hpp
        include/jforge/constant_pool/infos.hpp
        include/jforge/constant_pool/parser.hpp
        include/jforge/constant_pool/printer.hpp
        include/jforge/constant_pool/tags.hpp

        include/jforge/util/file.hpp
        include/jforge/util/span.hpp
        include/jforge/util/printing.hpp

        include/jforge/writer/constant_pool_writer.hpp

        include/jforge/bytecode/opcode.hpp
        include/jforge/builder/attribute_builder.hpp
        include/jforge/bytecode/instructions.hpp
        include/jforge/util/vector.hpp
        include/jforge/attributes/length.hpp
        include/jforge/attributes/names.hpp
        include/jforge/writer/attribute_writer.hpp
        include/jforge/writer/classfile_writer.hpp
)

set(SOURCE_FILES
        src/main.cpp

        src/jforge/attributes/parser.cpp
        src/jforge/attributes/printer.cpp

        src/jforge/builder/method_builder.cpp

        src/jforge/bytecode/decoder.cpp

        src/jforge/classfile/parser.cpp
        src/jforge/classfile/printer.cpp

        src/jforge/constant_pool/constant_pool.cpp
        src/jforge/constant_pool/hash.cpp
        src/jforge/constant_pool/parser.cpp
        src/jforge/constant_pool/printer.cpp
        src/jforge/constant_pool/tags.cpp
        src/jforge/writer/constant_pool_writer.cpp
        src/jforge/builder/class_builder.cpp
        src/jforge/builder/attribute_builder.cpp
        src/jforge/attributes/length.cpp
        include/jforge/writer/attribute_writer.hpp
        src/jforge/writer/attribute_writer.cpp
        src/jforge/writer/classfile_writer.cpp
)

add_executable(JForge ${INCLUDE_FILES} ${SOURCE_FILES})

target_include_directories(JForge PRIVATE include)
