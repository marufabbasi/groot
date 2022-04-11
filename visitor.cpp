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
        result = scope_->get(var)->val;
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
    std::shared_ptr<value> val = std::make_shared<value>(result);
    scope_->set("return", val);
    return val;
}

antlrcpp::Any visitor::visitAssignmentStatement(grootParser::AssignmentStatementContext *ctx)
{
    auto result = visit(ctx->expr);

    std::shared_ptr<value> val = std::make_shared<value>(result);
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

    if (!result.as<bool>() && ctx->elseblk != nullptr)
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
    if (!ctx->b->isEmpty())
    {
        return visit(ctx->b);
    }
    else if (!ctx->ib->isEmpty())
    {
        return visit(ctx->ib);
    }
}

antlrcpp::Any visitor::visitFunctionDefStatement(grootParser::FunctionDefStatementContext *ctx)
{
    auto fun_def = std::make_shared<function_def>();
    fun_def->name = ctx->name->getText();
    fun_def->body = ctx->blk;

    int parts = ctx->children.size();
    auto first_param_index = 3;
    auto last_param_index = parts - 2;

    for (int c = first_param_index; c < last_param_index; c += 2)
    {
        auto param = ctx->children[c]->getText();
        fun_def->parameters.push_back(param);
    }

    std::shared_ptr<value> val = std::make_shared<value>();
    val->val = fun_def;
    scope_->set(fun_def->name, val);

    auto fun_def_val = scope_->get(fun_def->name);

    if (fun_def_val->val.isNull())
    {
        return nullptr; // function not found
    }

    return val;
}

antlrcpp::Any visitor::visitFunctionCallExpression(grootParser::FunctionCallExpressionContext *ctx)
{
    std::string fun_name = ctx->name->getText();
    auto fun_def_val = scope_->get(fun_name);

    if (fun_def_val->val.isNull())
    {
        return nullptr; // function not found
    }

    auto fun_def = fun_def_val->val.as<std::shared_ptr<function_def>>();
    auto body = fun_def->body.as<grootParser::BlockContext *>();

    std::shared_ptr<scope> fun_scope = std::make_shared<scope>(scope_);

    int formal_param_count = fun_def->parameters.size();
    int parts = ctx->children.size();
    auto first_param_index = 2;
    auto last_param_index = parts - 1;

    int actual_param_count = 0;
    for (int c = first_param_index; c < last_param_index; c += 2)
    {
        auto param_name = fun_def->parameters[actual_param_count];
        auto param = ctx->children[c];
        auto param_val_n = visit(param).as<int>();
        auto param_val = std::make_shared<value>(param_val_n);
        fun_scope->set(param_name, param_val);
        actual_param_count++;
    }

    assert(formal_param_count == actual_param_count);

    scope_ = fun_scope;
    auto return_val = visit(body);
    scope_ = fun_scope->parent_scope_;
    return fun_scope->get("return")->val;
}
