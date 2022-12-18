
add_executable(pbl_compiler
    main.cpp
    lexer/lexer.cpp
)

target_compile_options(pbl_compiler PUBLIC --std=c++17)
target_include_directories(pbl_compiler PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)