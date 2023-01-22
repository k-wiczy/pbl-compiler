
add_executable(pbl_compiler
    main.cpp
    lexer/lexer.cpp
    parser/parser.cpp
    parser/parameter.cpp
    parser/port.cpp
    parser/pipe.cpp
    parser/instance.cpp
)

target_compile_options(pbl_compiler PUBLIC --std=c++17)
target_include_directories(pbl_compiler PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)