
#ifndef UXP1A_TUPLEPATTERN_H
#define UXP1A_TUPLEPATTERN_H

/**
 * Klasa reprezentująca wzorzec podawany w zapytaniu.
 */

#include "TuplePatternValue.h"
#include <vector>

class TuplePattern
{
private:
    std::vector<TuplePatternValue> values;
public:
    const std::vector<TuplePatternValue> &getValues() const;

    void setValues(const std::vector<TuplePatternValue> &values);

    void addValue(const TuplePatternValue& value);

};


#endif //UXP1A_TUPLEPATTERN_H
