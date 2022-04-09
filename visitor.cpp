//
// Created by maruf on 4/9/22.
//
#include <iostream>
#include "visitor.h"

const std::string TRUE_VALUE_STRING = "true";

antlrcpp::Any visitor::visitProgram(grootParser::ProgramContext *ctx)
{
    visitChildren(ctx);
    return result;
}

antlrcpp::Any visitor::visitAtomicValueExpression(grootParser::AtomicValueExpressionContext *ctx)
{
    if(ctx->atom->getType() == grootParser::INTEGER)
    {
        result = std::stoi(ctx->getText());
    }
    else if(ctx->atom->getType() == grootParser::BOOLEAN)
    {
        result = TRUE_VALUE_STRING.compare(ctx->atom->getText()) == 0;
    }

    return result;
}

antlrcpp::Any visitor::visitAddSubExpression(grootParser::AddSubExpressionContext *ctx)
{
    auto left = visit(ctx->left).as<int>();
    auto op = ctx->op->getText();
    auto right = visit(ctx->right).as<int>();
    result = 0;
    switch (op[0])
    {
        case '+':
            result = left + right;
            break;
        case '-':
            result = left - right;
            break;
    }

    return result;
}


antlrcpp::Any visitor::visitMulDivExpression(grootParser::MulDivExpressionContext *ctx)
{
    auto left = visit(ctx->left).as<int>();
    auto op = ctx->op->getText();
    auto right = visit(ctx->right).as<int>();

    result = 0;

    switch (op[0])
    {
        case '*':
            result = left * right;
            break;
        case '/':
            result = left / right;
            break;
    }

    return result;
}


antlrcpp::Any visitor::visitPrenEnclosedExpression(grootParser::PrenEnclosedExpressionContext *ctx)
{
    result = visit(ctx->expr).as<int>();
    return result;
}
