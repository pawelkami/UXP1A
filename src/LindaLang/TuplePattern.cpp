
#include "TuplePattern.h"



void TuplePattern::setValues(const std::vector<TuplePatternValue> &values)
{
    this->values = values;
}

const std::vector<TuplePatternValue> &TuplePattern::getValues() const
{
    return values;
}

void TuplePattern::addValue(const TuplePatternValue &value)
{
    values.push_back(value);
}

std::string TuplePattern::toString()
{
    std::string strValue = "(";
    for(int i = 0; i < this->values.size(); ++i)
        strValue += this->values[i].toString() + ",";
    strValue.pop_back();
    strValue.push_back(')');
    return strValue;
}


