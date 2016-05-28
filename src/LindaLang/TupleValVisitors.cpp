
#include "TupleValVisitors.h"


std::string GetTypeNameVis::operator()(int val) const
{
    return std::string("integer");
}


std::string GetTypeNameVis::operator()(float val) const
{
    return std::string("float");
}


std::string GetTypeNameVis::operator()(std::string val) const
{
    return std::string("string");
}


std::string ToStringVis::operator()(int val)const
{
    return std::string("Integer: " + std::to_string(val));
}


std::string ToStringVis::operator()(float val) const
{
    return std::string("Float: " + std::to_string(val));
}


std::string ToStringVis::operator()(std::string val) const
{
    return std::string("String: \"" + val + "\"");
}





