
#include "Tuple.h"

const std::vector<PValue> &Tuple::getValues() const
{
    return values;
}

void Tuple::setValues(const std::vector<PValue> &values)
{
    this->values = values;
}

bool Tuple::checkPattern(const TuplePattern &pattern)
{
    // TODO
    return false;
}





