//
// Created by maruf on 4/9/22.
//
#include <iostream>
#include <math.h>
#include <string>
#include "visitor.h"
#include "native_method.h"

const std::string TRUE_VALUE_STRING = "true";

visitor::visitor(std::shared_ptr<scope> scope)
{
    this->scope_ = scope;
}

antlrcpp::Any visitor::visitProgram(grootParser::ProgramContext *ctx)
{
    visitChildren(ctx);
    //scope_->print();
    return scope_->get("return");
}

antlrcpp::Any visitor::visitAtomicValueExpression(grootParser::AtomicValueExpressionContext *ctx)
{
    std::shared_ptr<value> result;
    if (ctx->atom->getType() == grootParser::INTEGER)
    {
        auto sval = ctx->atom->getText();
        auto val = std::stoi(sval);
        result = std::make_shared<int_value>(val);
    }
    else if (ctx->atom->getType() == grootParser::BOOLEAN)
    {
        result = std::make_shared<bool_value>(TRUE_VALUE_STRING.compare(ctx->atom->getText()) == 0);
    }
    else if (ctx->atom->getType() == grootParser::CHARACTER)
    {
        auto str = ctx->atom->getText();
        assert(str.length() == 3);
        if (str.length() == 3)
        {
            result = std::make_shared<char_value>(str[1]);
        }
    }
    else if (ctx->atom->getType() == grootParser::STRING)
    {
        auto str = ctx->atom->getText();
        assert(str.length() >= 2);
        if (str.length() >= 2)
        {
            result = std::make_shared<string_value>(str.substr(1, str.length() - 2)); //copy
        }
    }
    else if (ctx->atom->getType() == grootParser::IDENTIFIER)
    {
        auto var = ctx->atom->getText();
        result = scope_->get(var);
    }

    return result;
}

antlrcpp::Any visitor::visitAddSubExpression(grootParser::AddSubExpressionContext *ctx)
{
    auto left_result = reinterpret_cast<int_value *>(getValueFrom(visit(ctx->left)).get());
    auto op = ctx->op->getText();
    auto right_result = reinterpret_cast<int_value *>(getValueFrom(visit(ctx->right)).get());
    int left = left_result->val_, right = right_result->val_;

    int result = 0;

    switch (op[0])
    {
        case '+':
            result = left + right;
            break;
        case '-':
            result = left - right;
            break;
    }

    return std::shared_ptr<value>(new int_value(result));
}

antlrcpp::Any visitor::visitMulDivExpression(grootParser::MulDivExpressionContext *ctx)
{
    auto left_result = visit(ctx->left);
    auto right_result = visit(ctx->right);
    auto op = ctx->op->getText();

    auto left = dynamic_cast<int_value *>(getValueFrom(left_result).get())->val_;
    auto right = dynamic_cast<int_value *>(getValueFrom(right_result).get())->val_;

    int result = 0;

    switch (op[0])
    {
        case '*':
            result = left * right;
            break;
        case '/':
            result = left / right;
            break;
    }

    return std::shared_ptr<int_value>(new int_value(result));
}

antlrcpp::Any visitor::visitEqualityCheckExpression(grootParser::EqualityCheckExpressionContext *ctx)
{
    auto left_result = visit(ctx->left);
    auto op = ctx->op->getType();
    auto right_result = visit(ctx->right);

    bool result;

    if (left_result.isNull() || right_result.isNull())
    {
        if (op == grootParser::EQ)
        {
            result = left_result.isNull() && right_result.isNull();
        }
        else
        {
            result = !(left_result.isNull() && right_result.isNull());
        }
    }
    else
    {
        auto left = getValueFrom(left_result);
        auto right = getValueFrom(right_result);
        if (left->type_ == INTEGER && right->type_ == INTEGER)
        {
            switch (op)
            {
                case grootParser::EQ:
                    result = dynamic_cast<int_value *>(left.get())->val_ ==
                             dynamic_cast<int_value *>(right.get())->val_;
                    break;
                case grootParser::NE:
                    result = dynamic_cast<int_value *>(left.get())->val_ !=
                             dynamic_cast<int_value *>(right.get())->val_;
                    break;
            }
        }
        else if (left->type_ == CHARACTER && right->type_ == CHARACTER)
        {
            switch (op)
            {
                case grootParser::EQ:
                    result = dynamic_cast<char_value *>(left.get())->val_ ==
                             dynamic_cast<char_value *>(right.get())->val_;
                    break;
                case grootParser::NE:
                    result = dynamic_cast<char_value *>(left.get())->val_ !=
                             dynamic_cast<char_value *>(right.get())->val_;
                    break;
            }
        }
        else if (left->type_ == BOOLEAN && right->type_ == BOOLEAN)
        {
            switch (op)
            {
                case grootParser::EQ:
                    result = dynamic_cast<bool_value *>(left.get())->val_ ==
                             dynamic_cast<bool_value *>(right.get())->val_;
                    break;
                case grootParser::NE:
                    result = dynamic_cast<bool_value *>(left.get())->val_ !=
                             dynamic_cast<bool_value *>(right.get())->val_;
                    break;
            }
        }
    }
    return std::make_shared<bool_value>(result);
}

antlrcpp::Any visitor::visitNumericComparisonExpression(grootParser::NumericComparisonExpressionContext *ctx)
{
    auto left = dynamic_cast<int_value *> (getValueFrom(visit(ctx->left)).get());
    auto op = ctx->op->getType();
    auto right = dynamic_cast<int_value *> (getValueFrom(visit(ctx->right)).get());

    bool result;

    switch (op)
    {
        case grootParser::GT:
            result = left->val_ > right->val_;
            break;
        case grootParser::GE:
            result = left->val_ >= right->val_;
            break;
        case grootParser::LT:
            result = left->val_ < right->val_;
            break;
        case grootParser::LE:
            result = left->val_ <= right->val_;
            break;
    }

    return std::make_shared<bool_value>(result);
}

antlrcpp::Any visitor::visitPrenEnclosedExpression(grootParser::PrenEnclosedExpressionContext *ctx)
{
    auto result = getValueFrom(visit(ctx->expr));
    return result;
}

antlrcpp::Any visitor::visitReturnStatement(grootParser::ReturnStatementContext *ctx)
{
    auto result = visit(ctx->expr);
    auto v = result.is<std::shared_ptr<int_value>>();
    auto val = getValueFrom(result);
    scope_->set("return", val);
    return val;
}

antlrcpp::Any visitor::visitAssignmentStatement(grootParser::AssignmentStatementContext *ctx)
{
    auto var = ctx->var_name->getText();
    auto result = visit(ctx->expr);

    std::shared_ptr<value> val = getValueFrom(result);
    scope_->set(var, val);
    return val;
}

antlrcpp::Any visitor::visitUnaryOperationExpression(grootParser::UnaryOperationExpressionContext *ctx)
{
    auto op = ctx->op->getType();
    auto result = getValueFrom(visit(ctx->expr));

    std::shared_ptr<value> val;

    if (op == grootParser::NEG)
    {
        auto r = dynamic_cast<int_value *> (result.get());
        val = std::make_shared<int_value>(r->val_ * -1);
    }
    else
    {
        auto r = dynamic_cast<bool_value *> (result.get());
        val = std::make_shared<bool_value>(!r->val_);
    }

    return val;
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

    if (!result.as<std::shared_ptr<bool_value>>()->val_ && ctx->elseblk != nullptr)
    {
        result = visit(ctx->elseblk);
    }
    return result;
}

antlrcpp::Any visitor::visitIfblock(grootParser::IfblockContext *ctx)
{
    auto cond = visit(ctx->cond);
    if (cond.as<std::shared_ptr<bool_value>>()->val_)
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
    std::string name = ctx->name->getText();
    std::vector<std::string> parameters;

    int parts = ctx->children.size();
    auto first_param_index = 3;
    auto last_param_index = parts - 2;

    for (int c = first_param_index; c < last_param_index; c += 2)
    {
        auto param = ctx->children[c]->getText();
        parameters.push_back(param);
    }

    auto ftype =  VIRTUAL;

    if(0 == std::string("native").compare(ctx->ftype->getText()))
    {
        ftype = NATIVE;
    }

    auto body = ctx->blk;
    auto fun_def = std::make_shared<function_value>(name, body, parameters, ftype);
    scope_->set(name, fun_def);

    return fun_def;
}

antlrcpp::Any visitor::visitFunctionCallExpression(grootParser::FunctionCallExpressionContext *ctx)
{
    std::string fun_name = ctx->name->getText();
    function_value *fun_def = static_cast<function_value *>(scope_->get(fun_name).get());

    //todo: check if function was found

    std::shared_ptr<scope> fun_scope = std::make_shared<scope>(scope_);

    int formal_param_count = fun_def->parameters_.size();
    int parts = ctx->children.size();
    auto first_param_index = 2;
    auto last_param_index = parts - 1;

    int actual_param_count = 0;
    for (int c = first_param_index; c < last_param_index; c += 2)
    {
        auto param_name = fun_def->parameters_[actual_param_count];
        auto param = ctx->children[c];
        auto param_val = getValueFrom(visit(param));
        fun_scope->set(param_name, param_val);
        actual_param_count++;
    }

    assert(formal_param_count == actual_param_count);

    scope_ = fun_scope;
    if(fun_def->is_native())
    {
        native_method nm;
        nm.execute(fun_name, scope_);
    }
    else
    {
        auto body = fun_def->body_;
        auto return_val = visit(body);
    }
    scope_ = fun_scope->parent_scope_;
    return fun_scope->get("return");
}

antlrcpp::Any visitor::visitListValueExpression(grootParser::ListValueExpressionContext *ctx)
{
    std::vector<std::shared_ptr<value>> listValue;
    int startIndex = 1;
    int endIndex = ctx->children.size() - 1;

    for (int ci = startIndex; ci < endIndex; ci += 2)
    {
        auto val = visit(ctx->children[ci]);
        listValue.push_back(getValueFrom(val));
    }

    return std::make_shared<list_value>(listValue);
}

antlrcpp::Any visitor::visitItemAtIndexExpression(grootParser::ItemAtIndexExpressionContext *ctx)
{
    auto list = dynamic_cast<value *> (getValueFrom(visit(ctx->var_name)).get());

    if (list == nullptr)
    {
        return nullptr; // list not found
    }
    auto index = dynamic_cast<int_value *> (getValueFrom(visit(ctx->idx)).get());

    auto result = list->at(index->val_);

    return result;
}


std::shared_ptr<value> visitor::getValueFrom(antlrcpp::Any val)
{
    if (val.is<std::shared_ptr<value>>())
    {
        return val.as<std::shared_ptr<value>>();
    }
    else if (val.is<std::shared_ptr<int_value>>())
    {
        return val.as<std::shared_ptr<int_value>>();
    }
    else if (val.is<std::shared_ptr<char_value>>())
    {
        return val.as<std::shared_ptr<char_value>>();
    }
    else if (val.is<std::shared_ptr<bool_value>>())
    {
        return val.as<std::shared_ptr<bool_value>>();
    }
    else if (val.is<std::shared_ptr<list_value>>())
    {
        return val.as<std::shared_ptr<list_value>>();
    }
    else if (val.is<std::shared_ptr<string_value>>())
    {
        return val.as<std::shared_ptr<string_value>>();
    }
    else if (val.is<std::shared_ptr<function_value>>())
    {
        return val.as<std::shared_ptr<function_value>>();
    }

    assert(false);
}

antlrcpp::Any visitor::visitWhileloop(grootParser::WhileloopContext *ctx)
{
    auto cond = visit(ctx->cond);
    while (cond.as<std::shared_ptr<bool_value>>()->val_)
    {
        visit(ctx->blk);
        cond = visit(ctx->cond);
    }

    return cond;
}

antlrcpp::Any visitor::visitImportStatement(grootParser::ImportStatementContext *ctx)
{
    std::cout << " IMPORTING " << ctx->name->getText() << " AS " << ((ctx->alias) ? ctx->alias->getText() : " identity ") << std::endl;
    return grootBaseVisitor::visitImportStatement(ctx);
}
