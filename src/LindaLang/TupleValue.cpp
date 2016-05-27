#include "TupleValue.h"


template<class T>
std::string TupleValue<T>::toString()
{
    return this->getTypeName() + ":" + this->getStrValue();
}


template<class T>
T TupleValue<T>::getValue() const
{
    return value;
}

template<>
int TupleValue<int>::getValue() const
{
    return value;
}

template<class T>
void TupleValue<T>::setValue(T val)
{
    value = val;
}

template<>
void TupleValue<int>::setValue(int val)
{
    value = val;
}


template<>
std::string TupleValue<int>::getTypeName()
{
    return std::string("integer");
}


template<>
std::string TupleValue<float>::getTypeName()
{
    return std::string("float");
}


template<>
std::string TupleValue<std::string>::getTypeName()
{
    return std::string("string");
}


template<class T>
std::string TupleValue<T>::getTypeName()
{
    return std::string("unknown");
}


template<>
std::string TupleValue<int>::getStrValue()
{
    return std::to_string(value);
}


template<>
std::string TupleValue<float>::getStrValue()
{
    return std::to_string(value);
}


template<>
std::string TupleValue<std::string>::getStrValue()
{
    return std::string("\"" + value + "\"");
}


template<class T>
std::string TupleValue<T>::getStrValue()
{
    return std::string("unknown");
}
