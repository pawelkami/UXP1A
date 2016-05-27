//
// Created by tomasz on 5/27/16.
//

#ifndef UXP1A_VALUE_H
#define UXP1A_VALUE_H

#include <memory>

class Value
{
public:
    virtual ~Value();
};

typedef std::shared_ptr<Value> PValue;

#endif //UXP1A_VALUE_H
