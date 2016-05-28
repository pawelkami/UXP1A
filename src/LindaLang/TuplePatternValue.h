
#ifndef UXP1A_TUPLEPATTERNVALUE_H
#define UXP1A_TUPLEPATTERNVALUE_H

#include <boost/serialization/access.hpp>
#include "Enums.h"
#include <boost/variant.hpp>
#include <boost/serialization/variant.hpp>

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

    boost::variant<std::string, int, float> value;
public:
    void setCondition(Condition cond);
    Condition getCondition();
    std::string toString();
};


#endif //UXP1A_TUPLEPATTERNVALUE_H
