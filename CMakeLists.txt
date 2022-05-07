CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(groot)

SET(CMAKE_CXX_STANDARD 14)

find_package(antlr4-runtime REQUIRED)
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")

find_package(Catch2 3 REQUIRED)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/antlr/antlr-4.9.3-complete.jar)

include_directories(/usr/local/include/antlr4-runtime/ ${ANTLR4CPP_INCLUDE_DIRS})
link_directories(${ANTLR4CPP_LIBS})

execute_process(COMMAND java -jar ${ANTLR4CPP_JAR_LOCATION} -Dlanguage=Cpp -o parser -visitor groot.g4
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        RESULT_VARIABLE antlr4_result
        OUTPUT_VARIABLE antlr4_output)

if (${antlr4_result})
    message(FATAL_ERROR "antlr failed: ${antlr4_result}: ${antlr4_output}, CMake will exit.")
else ()
    message(STATUS "lex/parse file generated successfully.")
endif ()

add_executable(groot
        parser/grootLexer.cpp
        parser/grootParser.cpp
        parser/grootVisitor.cpp
        main.cpp
        visitor.cpp
        scope.cpp
        native_method.cpp
        grootListenerImpl.cpp
        )

add_dependencies(groot antlr4_static)

llvm_map_components_to_libnames(LLVM_LIBS support core irreader BitWriter orcjit native analysis
        Core
        ExecutionEngine
        InstCombine
        Object
        OrcJIT
        RuntimeDyld
        ScalarOpts
        Support
        native)

add_dependencies(groot antlr4_static)

target_link_libraries(groot PRIVATE antlr4_static ${LLVM_LIBS})

add_executable(tests
        parser/grootLexer.cpp
        parser/grootParser.cpp
        parser/grootVisitor.cpp
        visitor.cpp
        scope.cpp
        native_method.cpp
        tests/parser_tests.cpp)

target_include_directories(tests PRIVATE
        ${PROJECT_SOURCE_DIR}
        )

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain antlr4_static)

configure_file(example/test.groot test.groot COPYONLY)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS groot.g4)

set(UNIT_TEST tests)
add_custom_command(
        TARGET ${UNIT_TEST}
        COMMENT "Run tests"
        POST_BUILD
        COMMAND ${UNIT_TEST}
)
