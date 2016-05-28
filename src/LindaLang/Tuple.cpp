
#include "Tuple.h"


void Tuple::setValues(const std::vector<TupleValue> &values)
{
    this->values = values;
}

bool Tuple::checkPattern(const TuplePattern &pattern)
{
    // TODO
    return false;
}

const std::vector<TupleValue> &Tuple::getValues() const
{
    return this->values;
}


