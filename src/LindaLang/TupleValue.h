
#ifndef UXP1A_TUPLEVALUE_H
#define UXP1A_TUPLEVALUE_H

#include <string>
#include <memory>
#include "DetailedValue.h"

/**
 * Klasa reprezentująca pojedynczą wartość będącą w krotce,
 */

template<class T>
class TupleValue: public Value
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        //ar & boost::serialization::base_object(*this);
        ar & value;
    }

    T value;
public:
    T getValue() const;

    void setValue(T val);

    std::string getTypeName();
    std::string getStrValue();

    std::string toString();
};

//template class TupleValue<int>;
//template class TupleValue<std::string>;
//template class TupleValue<float>;


#endif //UXP1A_TUPLEVALUE_H
