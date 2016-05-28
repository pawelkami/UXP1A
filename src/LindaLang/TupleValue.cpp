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


bool TupleValue::fitsPattern(const TuplePatternValue &val)
{
    switch(val.getCondition())
    {
        case Condition::EQ: return boost::apply_visitor(ConditionVis<Condition::EQ>(), this->value, val.value);
        case Condition::GE: return boost::apply_visitor(ConditionVis<Condition::GE>(), this->value, val.value);
        case Condition::LE: return boost::apply_visitor(ConditionVis<Condition::LE>(), this->value, val.value);
        case Condition::GR: return boost::apply_visitor(ConditionVis<Condition::GR>(), this->value, val.value);
        case Condition::LS: return boost::apply_visitor(ConditionVis<Condition::LS>(), this->value, val.value);
        case Condition::ANY: return boost::apply_visitor(ConditionVis<Condition::ANY>(), this->value, val.value);
    }
}




