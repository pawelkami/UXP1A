
#include "Tuple.h"


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
    return true;
}

const std::vector<TupleValue> &Tuple::getValues() const
{
    return this->values;
}


