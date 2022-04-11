//
// Created by maruf on 4/9/22.
//

#include "scope.h"


scope::scope(std::shared_ptr<scope> parent)
{
    this->parent_scope_ = parent;
}

void scope::set(std::string identifier, std::shared_ptr<value> val)
{
    assert(identifier.length() > 0);
    value_map_[identifier] = val;
}

std::shared_ptr<value> scope::get(std::string identifier)
{
    if (value_map_.find(identifier) == value_map_.end())
    {
        if (this->parent_scope_ == nullptr)
        {
            return std::make_shared<value>();
        }
        else
        {
            return parent_scope_->get(identifier);
        }
    }

    return value_map_[identifier];
}

scope::~scope()
{
}
