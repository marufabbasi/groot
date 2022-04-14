//
// Created by maruf on 4/14/22.
//

#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include "antlr4-runtime.h"
#include "parser/grootLexer.h"
#include "parser/grootParser.h"
#include "parser/grootBaseVisitor.h"
#include "visitor.h"

TEST_CASE("Can load source file and parse", "[parser]")
{
    std::ifstream stream;

    stream.open("./test.groot");
    REQUIRE(stream.is_open());

    antlr4::ANTLRInputStream input(stream);

    grootLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    grootParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.prog();

    std::shared_ptr<scope> top_scope = std::make_shared<scope>();
    std::shared_ptr<grootVisitor> v = std::make_shared<visitor>(top_scope);


    auto return_val = v->visit(tree);
    auto result = reinterpret_cast<int_value *> (return_val.as<std::shared_ptr<value>>().get());

    REQUIRE(result);
    REQUIRE(result->val_ == 2);
}