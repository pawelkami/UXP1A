#include "TupleValue.h"


std::string TupleValue::getTypeName()
{
    return boost::apply_visitor(GetTypeNameVis(), value);
}


std::string TupleValue::toString()
{
    return boost::apply_visitor(ToStringVis(), value);
}

TupleValue::TupleValue(std::string str)
{
    value = std::string(str);
}

TupleValue::TupleValue(int integer)
{
    value = int(integer);
}

TupleValue::TupleValue(float floatingPoint)
{
    value = float(floatingPoint);
}





