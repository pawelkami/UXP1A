
#ifndef UXP1A_TUPLESPACE_H
#define UXP1A_TUPLESPACE_H

#include "Tuple.h"
#include "TuplePattern.h"

/**
 * Klasa reprezentująca przestrzeń krotek
 */
class TupleSpace
{
public:

    TupleSpace();

    void insertTuple(Tuple& tuple);

    bool getTuple(TuplePattern& pattern, Tuple& tuple);

    bool removeTuple(TuplePattern& pattern);

private:
    std::vector<Tuple> tuples;

    std::vector<Tuple>::iterator findTuple(TuplePattern& tuple);

};


#endif //UXP1A_TUPLESPACE_H
