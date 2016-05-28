
#include "TuplePattern.h"



void TuplePattern::setValues(const std::vector<TuplePatternValue> &values)
{
    this->values = values;
}

const std::vector<TuplePatternValue> &TuplePattern::getValues() const
{
    return values;
}
