//
// Created by maruf on 4/9/22.
//
#include <iostream>
#include <math.h>
#include "visitor.h"

const std::string TRUE_VALUE_STRING = "true";

visitor::visitor(std::shared_ptr<scope> scope)
{
    this->scope_ = scope;
}

antlrcpp::Any visitor::visitProgram(grootParser::ProgramContext *ctx)
{
    visitChildren(ctx);
    return scope_->get("return");
}

antlrcpp::Any visitor::visitAtomicValueExpression(grootParser::AtomicValueExpressionContext *ctx)
{
    antlrcpp::Any result;
    if (ctx->atom->getType() == grootParser::INTEGER)
    {
        result = std::stoi(ctx->getText());
    }
    else if (ctx->atom->getType() == grootParser::BOOLEAN)
    {
        result = TRUE_VALUE_STRING.compare(ctx->atom->getText()) == 0;
    }
    else if (ctx->atom->getType() == grootParser::STRING)
    {
        auto str = ctx->atom->getText();
        assert(str.length() >= 2);
        if (str.length() >= 2)
        {
            result = str.substr(1, str.length() - 2); //copy
        }
    }
    else if (ctx->atom->getType() == grootParser::IDENTIFIER)
    {
        auto var = ctx->atom->getText();
        result = scope_->get(var).value;
    }

    return result;
}

antlrcpp::Any visitor::visitAddSubExpression(grootParser::AddSubExpressionContext *ctx)
{
    auto left = visit(ctx->left).as<int>();
    auto op = ctx->op->getText();
    auto right = visit(ctx->right).as<int>();
    antlrcpp::Any result = 0;
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

    antlrcpp::Any result = 0;

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

    antlrcpp::Any result;

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

    antlrcpp::Any result;

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
    antlrcpp::Any result = visit(ctx->expr).as<int>();
    return result;
}

antlrcpp::Any visitor::visitReturnStatement(grootParser::ReturnStatementContext *ctx)
{
    auto result = visit(ctx->expr);
    value val(result);
    scope_->set("return", val);
    return val;
}

antlrcpp::Any visitor::visitAssignmentStatement(grootParser::AssignmentStatementContext *ctx)
{
    auto result = visit(ctx->expr);

    value val(result);
    auto var = ctx->var->getText();
    scope_->set(var, val);

    return val;
}

antlrcpp::Any visitor::visitUnaryOperationExpression(grootParser::UnaryOperationExpressionContext *ctx)
{
    auto op = ctx->op->getType();
    auto result = visit(ctx->expr);
    if (op == grootParser::NEG)
    {
        auto r = result.as<int>();
        r *= -1;
        return r;
    }
    else
    {
        auto r = result.as<bool>();
        r = !r;
        return r;
    }
}

antlrcpp::Any visitor::visitPowerExpression(grootParser::PowerExpressionContext *ctx)
{
    auto base = visit(ctx->base).as<int>();
    auto p = visit(ctx->pow).as<int>();

    auto result = pow(base, p);

    return (int) result;
}

antlrcpp::Any visitor::visitIfStatement(grootParser::IfStatementContext *ctx)
{
    auto result = visit(ctx->ifblk);

    if(!result.as<bool>())
    {
        result = visit(ctx->elseblk);
    }
    return result;
}

antlrcpp::Any visitor::visitIfblock(grootParser::IfblockContext *ctx)
{
    auto cond = visit(ctx->cond);
    if (cond.as<bool>())
    {
        visit(ctx->blk);
    }
    return cond;
}

antlrcpp::Any visitor::visitElseblock(grootParser::ElseblockContext *ctx)
{
    if(!ctx->b->isEmpty())
    {
        return visit(ctx->b);
    }
    else if(!ctx->ib->isEmpty())
    {
        return visit(ctx->ib);
    }
}
