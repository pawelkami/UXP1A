//
// Created by tomasz on 5/28/16.
//

#ifndef UXP1A_CONDITIONVIS_H
#define UXP1A_CONDITIONVIS_H

#include <string>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/get.hpp>

#include "TupleValue.h"

#include <boost/variant/multivisitors.hpp>

#include "Enums.h"

template<Condition cond>
class ConditionVis: public boost::static_visitor<bool>
{
public:
    template<class T, class U>
    bool operator()(const T& val1, const U& val2) const
    {
        return false;
    }
    template<class T>
    bool operator()(const T& val1, const T& val2) const
    {
        return ConditionTraits<cond>::fulfilled(val1, val2);
    };
};

#endif //UXP1A_CONDITIONVIS_H>