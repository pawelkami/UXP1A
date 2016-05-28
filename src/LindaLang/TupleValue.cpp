#include "TupleValue.h"


Tuple TupleValue::getValue() const
{
    return value;
}


void TupleValue::setValue(Tuple val)
{
    value = val;
}


std::string TupleValue::getTypeName()
{
    return boost::apply_visitor(GetTypeNameVis(), value);
}


std::string TupleValue::toString()
{
    return boost::apply_visitor(ToStringVis(), value);
}
