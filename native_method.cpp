//
// Created by maruf on 4/14/22.
//

#include "native_method.h"

void print(std::shared_ptr<scope> s)
{
    string_value* value = dynamic_cast<string_value*>(s->get("value").get());
    std::cout << value->val_ << std::endl;
}

int native_method::execute(std::string name, std::shared_ptr<scope> s)
{
    if(std::string("print").compare(name) == 0)
    {
        print(s);
    }

    return 0;
}
