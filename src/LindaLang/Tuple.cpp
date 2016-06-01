
#include "Tuple.h"
#include "LindaLogger.h"


void Tuple::setValues(const std::vector<TupleValue> &values)
{
    this->values = values;
}

bool Tuple::checkPattern(const TuplePattern &pattern)
{
    if(this->values.size() != pattern.getValues().size())
        return false;
    for(int i = 0; i < this->values.size(); ++i)
    {
        if(!this->values[i].fitsPattern(pattern.getValues()[i]))
            return false;
    }

    LOG_INFO("Tuple " + toString() + " matches pattern " + pattern.toString());
    return true;
}

const std::vector<TupleValue> &Tuple::getValues() const
{
    return this->values;
}

void Tuple::addValue(const TupleValue& val)
{
    values.push_back(val);
}

std::string Tuple::toString() const
{
    std::string strValue = "(";
    for(int i = 0; i < this->values.size(); ++i)
        strValue += this->values[i].toString() + ',';
    strValue.pop_back();
    strValue.push_back(')');
    return strValue;
}




