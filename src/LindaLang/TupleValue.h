
#ifndef UXP1A_TUPLEVALUE_H
#define UXP1A_TUPLEVALUE_H

#include <string>
#include <memory>
#include <boost/serialization/access.hpp>
#include <boost/variant.hpp>
#include <boost/serialization/variant.hpp>

#include "TupleValVisitors.h"

/**
 * Klasa reprezentująca pojedynczą wartość będącą w krotce,
 */

typedef boost::variant<std::string, int, float> Tuple;

class TupleValue
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & value;
    }

     Tuple value;
public:
    Tuple getValue() const;
    void setValue(Tuple val);

    std::string getTypeName();
    std::string toString();
};

#endif //UXP1A_TUPLEVALUE_H
