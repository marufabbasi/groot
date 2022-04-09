//
// Created by maruf on 4/9/22.
//

#ifndef GROOT_VISITOR_H
#define GROOT_VISITOR_H

#include "parser/grootBaseVisitor.h"

class visitor: public grootBaseVisitor
{
public:
    virtual antlrcpp::Any visitProgram(grootParser::ProgramContext *ctx) override;

    virtual antlrcpp::Any visitAtomicValueExpression(grootParser::AtomicValueExpressionContext *ctx) override;

    virtual antlrcpp::Any visitAddSubExpression(grootParser::AddSubExpressionContext *ctx) override;
    virtual antlrcpp::Any visitMulDivExpression(grootParser::MulDivExpressionContext *ctx) override;

    virtual antlrcpp::Any visitPrenEnclosedExpression(grootParser::PrenEnclosedExpressionContext *ctx) override;

private:
    int result; // since we do not have a way to call exit(int) yet we just return the lst calculated value
};


#endif //GROOT_VISITOR_H
