//
// Created by maruf on 4/9/22.
//

#ifndef GROOT_VISITOR_H
#define GROOT_VISITOR_H

#include "parser/grootBaseVisitor.h"

class visitor : public grootBaseVisitor
{
public:
    virtual antlrcpp::Any visitProgram(grootParser::ProgramContext *ctx) override;

    virtual antlrcpp::Any visitAtomicValueExpression(grootParser::AtomicValueExpressionContext *ctx) override;

    virtual antlrcpp::Any visitAddSubExpression(grootParser::AddSubExpressionContext *ctx) override;

    virtual antlrcpp::Any visitMulDivExpression(grootParser::MulDivExpressionContext *ctx) override;

    virtual antlrcpp::Any visitPrenEnclosedExpression(grootParser::PrenEnclosedExpressionContext *ctx) override;

    virtual antlrcpp::Any visitEqualityCheckExpression(grootParser::EqualityCheckExpressionContext *ctx) override;

    virtual antlrcpp::Any
    visitNumericComparisonExpression(grootParser::NumericComparisonExpressionContext *ctx) override;

    virtual antlrcpp::Any visitReturnStatement(grootParser::ReturnStatementContext *ctx) override;

private:
    antlrcpp::Any returnValue;
};


#endif //GROOT_VISITOR_H
