
#ifndef UXP1A_LINDA_H
#define UXP1A_LINDA_H


#include <ctime>
#include "Tuple.h"
#include "TuplePattern.h"
#include "Pipe.h"

/**
 * Klasa umożliwiająca pobieranie oraz dodawanie krotek do przestrzeni krotek.
 */
class Linda
{
private:
    Pipe pipe;

public:
    Linda(const Pipe& p);

    bool output(const Tuple& tuple);

    bool read(const TuplePattern& pattern, unsigned timeout, Tuple& returnTuple);

    bool input(const TuplePattern& pattern, unsigned timeout, Tuple& returnTuple);

};


#endif //UXP1A_LINDA_H
