//
// Created by tomasz on 5/27/16.
//

#ifndef UXP1A_TUPLEPATTERNVALUE_H
#define UXP1A_TUPLEPATTERNVALUE_H

#include "DetailedValue.h"
#include "Enums.h"

template<class T>
class TuplePatternValue: public DetailedValue<T>
{
private:
    Condition condition;
public:
    void setCondition(Condition cond);
    Condition getCondition();
    std::string toString();
};


#endif //UXP1A_TUPLEPATTERNVALUE_H
