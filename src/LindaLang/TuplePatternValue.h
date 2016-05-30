
#ifndef UXP1A_TUPLEPATTERNVALUE_H
#define UXP1A_TUPLEPATTERNVALUE_H

#include <boost/serialization/access.hpp>
#include "Conditions.h"
#include <boost/variant.hpp>
#include <boost/serialization/variant.hpp>

typedef boost::variant<std::string, int, float> TupleVariant;

class TuplePatternValue
{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & condition;
        ar & value;
    }

    Condition condition;

public:
    TupleVariant value;

    void setCondition(Condition cond);

    const Condition getCondition() const;

    TuplePatternValue();

    TuplePatternValue(int value);

    TuplePatternValue(float value);

    TuplePatternValue(const std::string& value);

    TuplePatternValue(int value, Condition c);

    TuplePatternValue(float value, Condition c);

    TuplePatternValue(const std::string& value, Condition c);

    std::string getTypeName() const;
    
    std::string toString() const;
};


#endif //UXP1A_TUPLEPATTERNVALUE_H
