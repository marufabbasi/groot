//
// Created by maruf on 5/6/22.
//

#ifndef GROOT_GROOTLISTENERIMPL_H
#define GROOT_GROOTLISTENERIMPL_H

#include "parser/grootBaseListener.h"

class grootListenerImpl: public grootBaseListener
{
public:
    virtual void exitAtomicValueExpression(grootParser::AtomicValueExpressionContext *ctx) override;
    virtual void exitAssignmentStatement(grootParser::AssignmentStatementContext *ctx) override;
    virtual void exitMulDivExpression(grootParser::MulDivExpressionContext *ctx) override;
    virtual void exitAddSubExpression(grootParser::AddSubExpressionContext *ctx) override;

    virtual void exitReturnStatement(grootParser::ReturnStatementContext *ctx) override;

    virtual void enterFunctionCallExpression(grootParser::FunctionCallExpressionContext *ctx) override;
    virtual void exitFunctionCallExpression(grootParser::FunctionCallExpressionContext *ctx) override;

    virtual void enterWhileloop(grootParser::WhileloopContext *ctx) override;
    virtual void exitWhileloop(grootParser::WhileloopContext *ctx) override;


};


#endif //GROOT_GROOTLISTENERIMPL_H
