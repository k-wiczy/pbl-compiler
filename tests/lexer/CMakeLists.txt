add_executable(lexer_unit_test
    lexer_unit_test.cpp
    ${CMAKE_SOURCE_DIR}/src/lexer/lexer.cpp
)

target_include_directories(lexer_unit_test PUBLIC
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(lexer_unit_test PUBLIC
    GTest::GTest
)

target_compile_options(lexer_unit_test PUBLIC --std=c++17)

file(COPY basic.pbl DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY comments.pbl DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY numeric.pbl DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY string.pbl DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY preprocessor.pbl DESTINATION ${CMAKE_BINARY_DIR}/bin)

add_test(
    NAME
        lexer_unit_test
    COMMAND
        ./lexer_unit_test
    WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/bin
)