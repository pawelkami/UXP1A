
#ifndef UXP1A_TUPLEVALUE_H
#define UXP1A_TUPLEVALUE_H

#include <string>
#include <memory>
#include "DetailedValue.h"

/**
 * Klasa reprezentująca pojedynczą wartość będącą w krotce,
 */

template<class T>
class TupleValue: public DetailedValue<T>
{
public:
    std::string toString();
};


#endif //UXP1A_TUPLEVALUE_H
