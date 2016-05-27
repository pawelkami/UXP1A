
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
    std::vector<PValue> values;
public:
    const std::vector<PValue> &getValues() const;

    void setValues(const std::vector<PValue> &values);

};


#endif //UXP1A_TUPLEPATTERN_H
