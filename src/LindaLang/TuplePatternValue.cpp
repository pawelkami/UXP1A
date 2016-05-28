
#include "TuplePatternValue.h"
#include "TupleValVisitors.h"

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
    std::string str;
    str += boost::apply_visitor(ToStringVis(), value);
    std::string temp = str.substr(0, str.find_first_of(":")+2);
    temp += getconditionTypeName(condition);
    temp += str.substr(str.find_first_of(":")+1);
    return temp;
}

TuplePatternValue::TuplePatternValue(int value)
{
    this->value = value;
    condition = Condition::EQ;
}

TuplePatternValue::TuplePatternValue(float value)
{
    this->value = value;
    condition = Condition::EQ;
}

TuplePatternValue::TuplePatternValue(const std::string &value)
{
    this->value = value;
    condition = Condition::EQ;
}

TuplePatternValue::TuplePatternValue(int value, Condition c)
{
    this->value = value;
    condition = c;
}

TuplePatternValue::TuplePatternValue(float value, Condition c)
{
    this->value = value;
    condition = c;
}

TuplePatternValue::TuplePatternValue(const std::string &value, Condition c)
{
    this->value = value;
    condition = c;
}

std::string TuplePatternValue::getTypeName()
{
    return boost::apply_visitor(GetTypeNameVis(), value);
}








