//
// Created by maruf on 4/9/22.
//

#include <iostream>

#include "antlr4-runtime.h"
#include "parser/grootLexer.h"
#include "parser/grootParser.h"
#include "parser/grootBaseVisitor.h"
#include "visitor.h"
#include "parser/grootBaseListener.h"
#include "grootListenerImpl.h"

using namespace antlr4;

int main(int argc, const char *argv[])
{
    std::ifstream stream;
    if (argc < 2)
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

    auto listener = std::make_shared<grootListenerImpl>();
    tree::ParseTreeWalker::DEFAULT.walk(listener.get(), tree);

    return 0;
}
