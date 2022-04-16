
```cmake
find_package(Catch2 3 REQUIRED)
add_executable(tests
        parser/grootLexer.cpp
        parser/grootParser.cpp
        parser/grootVisitor.cpp
        visitor.cpp
        scope.cpp
        native_method.cpp
        tests/parser_tests.cpp)

target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain antlr4_static)

configure_file(example/test.groot test.groot COPYONLY)

set(UNIT_TEST tests)
add_custom_command(
        TARGET ${UNIT_TEST}
        COMMENT "Run tests"
        POST_BUILD
        COMMAND ${UNIT_TEST}
)
```