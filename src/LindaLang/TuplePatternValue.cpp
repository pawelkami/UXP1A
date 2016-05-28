
#include "TuplePatternValue.h"


void TuplePatternValue::setCondition(Condition cond)
{
    condition = cond;
}


const Condition TuplePatternValue::getCondition() const
{
    return condition;
}


std::string TuplePatternValue::toString()
{
    // TODO
    //return this->getTypeName() + ":" + getconditionTypeName(this->getCondition()) + this->getStrValue();
    return "";
}