# Specifying the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project Name and Programming Language
project(AegisCompiler LANGUAGES CXX)

# Specify the C++ standard (We recommend using modern C++20 or C++17 for Aegis development)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the output location for the executable file (.exe)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_SOURCE_DIR}/bin")
endforeach()

# Specify the name of the executable file and the source files to include in the build
add_executable(main
    src/main.cpp
    src/ast/lexer.cpp
    src/syntax/parser.cpp
    src/runtime/interpreter.cpp
)

# Specifying the include path (where to look for header files)
target_include_directories(main PRIVATE src)