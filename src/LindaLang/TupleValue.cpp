#include "TupleValue.h"


std::string TupleValue::getTypeName() const
{
    return boost::apply_visitor(GetTypeNameVis(), value);
}


std::string TupleValue::toString() const
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
        default: return false;
    }
}

TupleValue::TupleValue()
{

}






