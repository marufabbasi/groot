#include <iostream>

#include "antlr4-runtime.h"
#include "parser/grootLexer.h"
#include "parser/grootParser.h"
#include "parser/grootBaseListener.h"
#include "parser/grootBaseVisitor.h"

using namespace antlr4;

int main(int argc, const char* argv[]) {
  std::ifstream stream;
  
  stream.open(argv[1]);
  ANTLRInputStream input(stream);

  grootLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  grootParser parser(&tokens);

  tree::ParseTree *tree = parser.program();
  grootVisitor *visitor = new grootBaseVisitor();
  auto result = visitor->visit(tree);

  return 0;
}
