
#ifndef UXP1A_LINDA_H
#define UXP1A_LINDA_H


#include <ctime>
#include "Tuple.h"
#include "TuplePattern.h"

class Linda
{
private:

public:
    bool output(const Tuple& tuple);

    bool read(const TuplePattern& pattern, time_t timeout, Tuple& returnTuple);

    bool input(const TuplePattern& pattern, time_t timeout, Tuple& returnTuple);

};


#endif //UXP1A_LINDA_H
