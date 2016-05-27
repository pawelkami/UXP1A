
#include "DetailedValue.h"


template<class T>
T DetailedValue<T>::getValue() const
{
    return value;
}


template<class T>
void DetailedValue<T>::setValue(T val)
{
    value = val;
}


template<>
std::string DetailedValue<int>::getTypeName()
{
    return std::string("integer");
}


template<>
std::string DetailedValue<float>::getTypeName()
{
    return std::string("float");
}


template<>
std::string DetailedValue<std::string>::getTypeName()
{
    return std::string("string");
}


template<class T>
std::string DetailedValue<T>::getTypeName()
{
    return std::string("unknown");
}


template<>
std::string DetailedValue<int>::getStrValue()
{
    return std::to_string(value);
}


template<>
std::string DetailedValue<float>::getStrValue()
{
    return std::to_string(value);
}


template<>
std::string DetailedValue<std::string>::getStrValue()
{
    return std::string("\"" + value + "\"");
}


template<class T>
std::string DetailedValue<T>::getStrValue()
{
    return std::string("unknown");
}