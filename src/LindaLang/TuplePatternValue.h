
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
    const Condition getCondition() const;
    std::string toString();
};


#endif //UXP1A_TUPLEPATTERNVALUE_H
