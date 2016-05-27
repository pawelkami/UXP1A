
#include "TuplePattern.h"

const std::vector<PValue> &TuplePattern::getValues() const
{
    return values;
}

void TuplePattern::setValues(const std::vector<PValue> &values)
{
    this->values = values;
}