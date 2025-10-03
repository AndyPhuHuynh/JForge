cmake_minimum_required(VERSION 3.5)
project(JForge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_FILES
        include/jforge/access/flags.hpp

        include/jforge/attributes/attributes.hpp
        include/jforge/attributes/printer.hpp
        include/jforge/attributes/parser.hpp

        include/jforge/bytecode/decoder.hpp
        include/jforge/bytecode/instructions.hpp

        include/jforge/classfile/classfile.hpp
        include/jforge/classfile/method.hpp
        include/jforge/classfile/parser.hpp
        include/jforge/classfile/printer.hpp

        include/jforge/constant_pool/constant_pool.hpp
        include/jforge/constant_pool/infos.hpp
        include/jforge/constant_pool/parser.hpp
        include/jforge/constant_pool/printer.hpp
        include/jforge/constant_pool/tags.hpp

        include/jforge/util/file.hpp
        include/jforge/opcode.hpp
)

set(SOURCE_FILES
        src/main.cpp

        src/jforge/attributes/parser.cpp
        src/jforge/attributes/printer.cpp

        src/jforge/bytecode/decoder.cpp

        src/jforge/classfile/parser.cpp
        src/jforge/classfile/printer.cpp

        src/jforge/constant_pool/parser.cpp
        src/jforge/constant_pool/tags.cpp
        src/jforge/constant_pool/printer.cpp
)

add_executable(JForge ${INCLUDE_FILES} ${SOURCE_FILES})

target_include_directories(JForge PRIVATE include)
