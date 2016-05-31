
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

std::string TuplePattern::toString() const
{
    std::string strValue = "(";
    for(auto& v : this->values)
    {
        strValue += v.toString() + ",";
    }
    strValue.pop_back();
    strValue.push_back(')');
    return strValue;
}


