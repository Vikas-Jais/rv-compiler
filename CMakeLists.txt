cmake_minimum_required(VERSION 3.20)

project(rv-compiler
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(rv
    src/main.cpp
    src/Lexer.cpp
    src/LexerError.cpp
)

target_include_directories(rv
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

add_executable(rv_tests
    tests/lexer_tests.cpp
    src/Lexer.cpp
    src/LexerError.cpp
)

target_include_directories(rv_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(
    NAME lexer_tests
    COMMAND rv_tests
)