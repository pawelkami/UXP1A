#include "TupleValue.h"


template<class T>
std::string TupleValue<T>::toString()
{
    return this->getTypeName() + ":" + this->getStrValue();
}



