//
// Created by maruf on 4/9/22.
//

#include <iostream>

#include "antlr4-runtime.h"
#include "parser/grootLexer.h"
#include "parser/grootParser.h"
#include "parser/grootBaseListener.h"
#include "parser/grootBaseVisitor.h"
#include "visitor.h"

using namespace antlr4;

int main(int argc, const char *argv[])
{
    std::ifstream stream;
    if (argc<2)
    {
        std::cerr << "Usage: " << argv[0] << " <source file>" << std::endl;
    }


    stream.open(argv[1]);
    if (!stream.is_open())
    {
        std::cerr << "Can not open input file " << argv[1] << std::endl;
    }

    ANTLRInputStream input(stream);

    grootLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    grootParser parser(&tokens);

    tree::ParseTree *tree = parser.prog();
    grootVisitor *v = new visitor();
    auto result = v->visit(tree);
    if(result.is<int>())
    {
        std::cout << result.as<int>() << std::endl;
    }
    else if(result.is<bool>())
    {
        std::cout << result.as<bool>() << std::endl;
    }

    return 0;
}
