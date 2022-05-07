//
// Created by maruf on 5/6/22.
//

#include "grootListenerImpl.h"

void grootListenerImpl::exitAtomicValueExpression(grootParser::AtomicValueExpressionContext *ctx)
{
    std::cout << ctx->atom->getType() << " " << ctx->atom->getText() << std::endl;
}

void grootListenerImpl::exitAssignmentStatement(grootParser::AssignmentStatementContext *ctx)
{
    std::cout << ctx->var_name->getText() << " = " << ctx->expr->getText() << std::endl;
}

void grootListenerImpl::exitMulDivExpression(grootParser::MulDivExpressionContext *ctx)
{
    std::cout << ctx->left->getText() << ctx->op->getText() << ctx->right->getText() << std::endl;
}

void grootListenerImpl::exitAddSubExpression(grootParser::AddSubExpressionContext *ctx)
{
    std::cout << ctx->left->getText() << ctx->op->getText() << ctx->right->getText() << std::endl;
}

void grootListenerImpl::exitReturnStatement(grootParser::ReturnStatementContext *ctx)
{
    std::cout << "return " << ctx->expr->getText() << std::endl;
}

void grootListenerImpl::enterFunctionCallExpression(grootParser::FunctionCallExpressionContext *ctx)
{
    std::cout << "()=> { " << ctx->name->getText() << std::endl;
}

void grootListenerImpl::exitFunctionCallExpression(grootParser::FunctionCallExpressionContext *ctx)
{
    std::cout << " } " << ctx->name->getText() << std::endl;
}

void grootListenerImpl::enterWhileloop(grootParser::WhileloopContext *ctx)
{
    std::cout << "while " << ctx->cond->getText() << " {" << std::endl;
}

void grootListenerImpl::exitWhileloop(grootParser::WhileloopContext *ctx)
{
    std::cout << " } while " << ctx->cond->getText() << "" << std::endl;
}
