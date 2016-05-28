
#ifndef UXP1A_TUPLEVALUE_H
#define UXP1A_TUPLEVALUE_H

#include <string>
#include <sstream>
#include <memory>
#include <boost/serialization/access.hpp>
#include <boost/variant.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/any.hpp>

#include "TupleValVisitors.h"
#include "TuplePatternValue.h"
#include "ConditionVis.h"

/**
 * Klasa reprezentująca pojedynczą wartość będącą w krotce,
 */


class TupleValue
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & value;
    }

public:
    TupleVariant value;

    TupleValue();

    TupleValue(std::string str);

    TupleValue(int integer);

    TupleValue(float floatingPoint);

    boost::any getValue(std::string type);

    bool fitsPattern(const TuplePatternValue& val);

    int getInteger();

    std::string getString();

    float getFloat();

    std::string getTypeName();
    std::string toString();
};

#endif //UXP1A_TUPLEVALUE_H
