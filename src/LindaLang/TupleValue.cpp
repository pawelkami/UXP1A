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

boost::any TupleValue::getValue(std::string type)
{
    if(type.compare("string") == 0)
        return getString();
    else if(type.compare("integer") == 0)
        return getInteger();
    else if(type.compare("float") == 0)
        return getFloat();
    else
        throw std::string("Unknown type!");
}

int TupleValue::getInteger()
{
    return boost::get<int>(value);
}

float TupleValue::getFloat()
{
    return boost::get<float>(value);
}

std::string TupleValue::getString()
{
    return boost::get<std::string>(value);
}





