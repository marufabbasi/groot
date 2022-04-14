//
// Created by maruf on 4/9/22.
//

#ifndef GROOT_SCOPE_H
#define GROOT_SCOPE_H

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>

#include "antlr4-runtime.h"
#include "parser/grootParser.h"

extern int gcounter;

enum value_type : int
{
    INTEGER,
    BOOLEAN,
    CHARACTER,
    STRING,
    LIST,
    FUNCTION
};


enum function_type : int
{
    VIRTUAL,
    STATIC,
    SPECIAL,
    NATIVE
};

class value
{
public:
    value()
    { id = gcounter++; }

    virtual std::shared_ptr<value> at(int index)
    {
        throw std::bad_typeid();
    };

    value_type type_;

    virtual void print()
    {
        assert(false);
    }

    int id;
};

class int_value : public value
{
public:
    int_value() = default;

    explicit int_value(int val)
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
    bool_value() = default;

    explicit bool_value(bool val)
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

class char_value : public value
{
public:
    char_value() = default;

    explicit char_value(char val)
    {
        val_ = val;
        type_ = CHARACTER;
    }

    void print() override
    {
        std::cout << id << ": " << type_ << " => " << val_;
    }

    char val_;
};


class string_value : public value
{
public:
    string_value() = default;

    explicit string_value(std::string val)
    {
        val_ = std::move(val);
        type_ = STRING;
    }

    virtual std::shared_ptr<value> at(int index) override
    {
        auto val = val_.at(index);
        std::make_shared<char_value>(val);
    };

    void print() override
    {
        std::cout << id << ": " << type_ << " => " << val_;
    }

    std::string val_;
};


class list_value : public value
{
public:
    list_value() = default;

    explicit list_value(std::vector<std::shared_ptr<value>> val)
    {
        val_ = std::move(val);
        type_ = LIST;
    }

    std::shared_ptr<value> at(int index) override
    {
        return val_.at(index);
    }

    void print() override
    {
        std::cout << id << ": " << type_ << "[";
        for (auto v: val_)
        {
            v->print();
            std::cout << ", ";
        }

        std::cout << "]" << std::endl;
    }

    std::vector<std::shared_ptr<value>> val_;
};

class function_value : public value
{
public:
    function_value() = default;

    function_value(std::string name, grootParser::BlockContext *body, std::vector<std::string> parameters, function_type ft=VIRTUAL)
    {
        assert(ft!=NATIVE || body == nullptr);
        name_ = std::move(name);
        body_ = body;
        parameters_ = std::move(parameters);
        type_ = FUNCTION;
        function_type_ = ft;
    }

    void print() override
    {
        std::cout << id << ": " << "function " << name_ << "(...) {...}";
    }

    bool is_native()
    {
        return function_type_ == NATIVE;
    }

    function_type function_type_;
    std::string name_;
    grootParser::BlockContext *body_{}; //lifefunction_type function_type_;time is managed by parser
    std::vector<std::string> parameters_;
};

class scope
{
public:
    std::shared_ptr<scope> parent_scope_;
public:
    explicit scope(std::shared_ptr<scope> parent = nullptr);

    ~scope();

    void set(std::string identifier, std::shared_ptr<value> val);

    std::shared_ptr<value> get(std::string identifier);

    void print();

private:
    std::unordered_map<std::string, std::shared_ptr<value>> value_map_;
};

#endif //GROOT_SCOPE_H
