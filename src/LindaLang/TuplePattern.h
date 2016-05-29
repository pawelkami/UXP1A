
#ifndef UXP1A_TUPLEPATTERN_H
#define UXP1A_TUPLEPATTERN_H

/**
 * Klasa reprezentująca wzorzec podawany w zapytaniu.
 */

#include "TuplePatternValue.h"
#include <vector>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

class TuplePattern
{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & values;
    }

    std::vector<TuplePatternValue> values;
public:
    const std::vector<TuplePatternValue> &getValues() const;

    void setValues(const std::vector<TuplePatternValue> &values);

    void addValue(const TuplePatternValue& value);

};


#endif //UXP1A_TUPLEPATTERN_H
