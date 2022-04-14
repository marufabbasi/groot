//
// Created by maruf on 4/14/22.
//

#ifndef GROOT_NATIVE_METHOD_H
#define GROOT_NATIVE_METHOD_H

#include <memory>
#include "scope.h"

class native_method
{
public:
    int execute(std::string name, std::shared_ptr<scope> s);
};


#endif //GROOT_NATIVE_METHOD_H
