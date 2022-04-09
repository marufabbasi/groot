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
    if (ctx->atom->getType() == grootParser::INTEGER)
    {
        result = std::stoi(ctx->getText());
    }
    else if (ctx->atom->getType() == grootParser::BOOLEAN)
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

antlrcpp::Any visitor::visitEqualityCheckExpression(grootParser::EqualityCheckExpressionContext *ctx)
{
    auto left = visit(ctx->left);
    auto op = ctx->op->getType();
    auto right = visit(ctx->right);

    if (left.isNull() || right.isNull())
    {
        if (op == grootParser::EQ)
        {
            result = left.isNull() && right.isNull();
        }
        else
        {
            result = !(left.isNull() && right.isNull());
        }
    }
    else if (left.is<int>() && right.is<int>())
    {
        switch (op)
        {
            case grootParser::EQ:
                result = left.as<int>() == right.as<int>();
                break;
            case grootParser::NE:
                result = left.as<int>() != right.as<int>();
                break;
        }
    }
    else if (left.is<bool>() && right.is<bool>())
    {
        switch (op)
        {
            case grootParser::EQ:
                result = left.as<bool>() == right.as<bool>();
                break;
            case grootParser::NE:
                result = left.as<bool>() != right.as<bool>();
                break;
        }
    }

    return result;
}

antlrcpp::Any visitor::visitNumericComparisonExpression(grootParser::NumericComparisonExpressionContext *ctx)
{
    auto left = visit(ctx->left).as<int>();
    auto op = ctx->op->getType();
    auto right = visit(ctx->right).as<int>();

    switch (op)
    {
        case grootParser::GT:
            result = left > right;
            break;
        case grootParser::GE:
            result = left >= right;
            break;
        case grootParser::LT:
            result = left < right;
            break;
        case grootParser::LE:
            result = left < right;
            break;
    }

    return result;
}

antlrcpp::Any visitor::visitPrenEnclosedExpression(grootParser::PrenEnclosedExpressionContext *ctx)
{
    result = visit(ctx->expr).as<int>();
    return result;
}
