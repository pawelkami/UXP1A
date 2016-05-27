//
// Created by tomasz on 5/27/16.
//

#include "TuplePatternValue.h"


template<class T>
void TuplePatternValue<T>::setCondition(Condition cond)
{
    condition = cond;
}


template<class T>
Condition TuplePatternValue<T>::getCondition()
{
    return condition;
}


template<class T>
std::string TuplePatternValue<T>::toString()
{
    return this->getTypeName() + ":" + getconditionTypeName(this->getCondition()) + this->getStrValue();
}