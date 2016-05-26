#include "TupleValue.h"

template<class T>
T DetailedTupleValue<T>::getValue() const
{
    return value;
}

template<class T>
void DetailedTupleValue<T>::setValue(T val)
{
    value = val;
}

template<>
std::string DetailedTupleValue<int>::getTypeName() const
{
    return std::string("integer");
}

template<class T>
std::string DetailedTupleValue<T>::toString() const
{
    return getTypeName() + ": " + value;
}


template<>
std::string DetailedTupleValue<float>::getTypeName() const
{
    return std::string("float");
}

template<>
std::string DetailedTupleValue<std::string>::getTypeName() const
{
    return std::string("string");
}




