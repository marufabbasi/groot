//
// Created by maruf on 4/9/22.
//

#ifndef GROOT_VISITOR_H
#define GROOT_VISITOR_H

#include <memory>
#include "parser/grootBaseVisitor.h"
#include "scope.h"

class visitor : public grootBaseVisitor
{
public:
    explicit visitor(std::shared_ptr<scope> scope);

    antlrcpp::Any visitProgram(grootParser::ProgramContext *ctx) override;

    antlrcpp::Any visitAtomicValueExpression(grootParser::AtomicValueExpressionContext *ctx) override;

    antlrcpp::Any visitAddSubExpression(grootParser::AddSubExpressionContext *ctx) override;

    antlrcpp::Any visitMulDivExpression(grootParser::MulDivExpressionContext *ctx) override;

    antlrcpp::Any visitPrenEnclosedExpression(grootParser::PrenEnclosedExpressionContext *ctx) override;

    antlrcpp::Any visitEqualityCheckExpression(grootParser::EqualityCheckExpressionContext *ctx) override;

    antlrcpp::Any visitNumericComparisonExpression(grootParser::NumericComparisonExpressionContext *ctx) override;

    antlrcpp::Any visitReturnStatement(grootParser::ReturnStatementContext *ctx) override;

    antlrcpp::Any visitAssignmentStatement(grootParser::AssignmentStatementContext *ctx) override;

    antlrcpp::Any visitUnaryOperationExpression(grootParser::UnaryOperationExpressionContext *ctx) override;

    antlrcpp::Any visitPowerExpression(grootParser::PowerExpressionContext *ctx) override;

    antlrcpp::Any visitIfStatement(grootParser::IfStatementContext *ctx) override;

    antlrcpp::Any visitIfblock(grootParser::IfblockContext *ctx) override;

    antlrcpp::Any visitElseblock(grootParser::ElseblockContext *ctx) override;

    antlrcpp::Any visitFunctionDefStatement(grootParser::FunctionDefStatementContext *ctx) override;

    antlrcpp::Any visitFunctionCallExpression(grootParser::FunctionCallExpressionContext *ctx) override;

    std::shared_ptr<value> getValueFrom(antlrcpp::Any val);

    antlrcpp::Any visitListValueExpression(grootParser::ListValueExpressionContext *ctx) override;

    antlrcpp::Any visitItemAtIndexExpression(grootParser::ItemAtIndexExpressionContext *ctx) override;

private:
    std::shared_ptr<scope> scope_;

};


#endif //GROOT_VISITOR_H
