
#include "TuplePatternValue.h"


void TuplePatternValue::setCondition(Condition cond)
{
    condition = cond;
}


Condition TuplePatternValue::getCondition()
{
    return condition;
}


std::string TuplePatternValue::toString()
{
    // TODO
    //return this->getTypeName() + ":" + getconditionTypeName(this->getCondition()) + this->getStrValue();
}