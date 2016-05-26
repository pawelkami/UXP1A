
#include "Tuple.h"

const std::vector<PTupleValue> &Tuple::getValues() const
{
    return values;
}

void Tuple::setValues(const std::vector<PTupleValue> &values)
{
    this->values = values;
}

bool Tuple::checkPattern(const TuplePattern &pattern)
{
    // TODO
    return false;
}





