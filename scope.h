//
// Created by maruf on 4/9/22.
//

#ifndef GROOT_SCOPE_H
#define GROOT_SCOPE_H

#include <iostream>
#include <unordered_map>
#include "antlr4-runtime.h"

typedef struct _value
{
    _value() { value = nullptr; }
    _value(antlrcpp::Any val)
    {
        value = val;
    }

    int type;
    antlrcpp::Any value;
} value;

class scope
{
public:
    scope(std::shared_ptr<scope> parent = nullptr);

    void set(std::string identifier, value val);

    value get(std::string identifier);

private:
    std::unordered_map<std::string, value> value_map_;
    std::shared_ptr<scope> parent_scope_;
};


#endif //GROOT_SCOPE_H
