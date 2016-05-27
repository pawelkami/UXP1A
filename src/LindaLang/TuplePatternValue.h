//
// Created by tomasz on 5/27/16.
//

#ifndef UXP1A_TUPLEPATTERNVALUE_H
#define UXP1A_TUPLEPATTERNVALUE_H

#include "DetailedValue.h"
#include "Enums.h"

template<class T>
class TuplePatternValue: public DetailedValue<T>
{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object(*this);
        ar & condition;
    }
    Condition condition;
public:
    void setCondition(Condition cond);
    Condition getCondition();
    std::string toString();
};


#endif //UXP1A_TUPLEPATTERNVALUE_H
