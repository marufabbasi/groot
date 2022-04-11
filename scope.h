//
// Created by maruf on 4/9/22.
//

#ifndef GROOT_SCOPE_H
#define GROOT_SCOPE_H

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include "antlr4-runtime.h"

typedef struct _function_def
{
    std::string name;
    antlrcpp::Any body;
    std::vector<std::string> parameters;
} function_def;

struct value
{
public:
    value()
    { this->val = nullptr; }

    value(antlrcpp::Any val)
    {
        this->val = val;
    }

    int type;
    antlrcpp::Any val;
};


class scope
{
public:
    std::shared_ptr<scope> parent_scope_;
public:
    scope(std::shared_ptr<scope> parent = nullptr);

    ~scope();

    void set(std::string identifier, std::shared_ptr<value> val);

    std::shared_ptr<value> get(std::string identifier);

private:
    std::unordered_map<std::string, std::shared_ptr<value>> value_map_;
};


#endif //GROOT_SCOPE_H
