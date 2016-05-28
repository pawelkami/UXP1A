
#ifndef UXP1A_TUPLEPATTERNVALUE_H
#define UXP1A_TUPLEPATTERNVALUE_H

#include <boost/serialization/access.hpp>
#include "Enums.h"
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

    Condition getCondition();

    TuplePatternValue(int value);

    TuplePatternValue(float value);

    TuplePatternValue(const std::string& value);

    TuplePatternValue(int value, Condition c);

    TuplePatternValue(float value, Condition c);

    TuplePatternValue(const std::string& value, Condition c);

    std::string getTypeName();

>>>>>>> dcf97161445662bdbba60bdddaeb575fece5b6bf
    std::string toString();
};


#endif //UXP1A_TUPLEPATTERNVALUE_H
