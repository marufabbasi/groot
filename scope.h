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
#include "parser/grootParser.h"

extern int gcounter;

enum value_type: int
{
    INTEGER,
    BOOLEAN,
    STRING,
    FUNCTION
};

class value
{
public:
    value() { id = gcounter++; }
    value_type type_;
    virtual void print() {}
    int id;
};

class int_value : public value
{
public:
    int_value() {}
    int_value(int val)
    {
        val_ = val;
        type_ = INTEGER;
    }

    void print() override
    {
        std::cout << id << ": " << type_ << " => " << val_;
    }

    int val_;
};

class bool_value : public value
{
public:
    bool_value() {}
    bool_value(bool val)
    {
        val_ = val;
        type_ = BOOLEAN;
    }

    void print() override
    {
        std::cout << id << ": " << type_ << " => " << val_;
    }

    bool val_;
};

class string_value : public value
{
public:
    string_value() {}
    string_value(std::string val)
    {
        val_ = val;
        type_ = STRING;
    }

    void print() override
    {
        std::cout << id << ": " << type_ << " => " << val_;
    }

    std::string val_;
};

class function_value : public value
{
public:
    function_value() {}
    function_value(std::string name, grootParser::BlockContext *body,  std::vector<std::string> parameters)
    {
        name_ = name;
        body_= body;
        parameters_ = parameters;
        type_ = FUNCTION;
    }


    void print() override
    {
        std::cout<< id << ": "  << "function " << name_ << "(...) {...}";
    }

    std::string name_;
    grootParser::BlockContext *body_; //lifetime is managed by parser
    std::vector<std::string> parameters_;
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
    void print();

private:
    std::unordered_map<std::string, std::shared_ptr<value>> value_map_;
};

#endif //GROOT_SCOPE_H
