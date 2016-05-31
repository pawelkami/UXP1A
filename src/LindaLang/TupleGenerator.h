

#ifndef UXP1A_TUPLEGENERATOR_H
#define UXP1A_TUPLEGENERATOR_H


#include "TupleValue.h"
#include "TuplePattern.h"
#include "Tuple.h"

#define MIN_TUPLE_LENGTH 2
#define MAX_TUPLE_LENGTH 4
#define FLOAT_IN_TUPLE_MAX 100.0
#define MAXSTRLEN 20
#define TUPLE_GENERATOR TupleGenerator::getInstance()

class TupleGenerator
{
private:
    std::vector<std::function<TupleValue ()> > tupleGenerator;

    std::vector<std::function<TuplePatternValue ()> > tuplePatternGenerator;

    void init();

    int generateInt();

    float generateFloat();

    std::string generateString();

    TupleValue generateStringTuple();

    TupleValue generateIntTuple();

    TupleValue generateFloatTuple();

    TuplePatternValue generateIntTuplePattern();

    TuplePatternValue generateFloatTuplePattern();

    TuplePatternValue generateStringTuplePattern();

    TupleGenerator();
public:

    static TupleGenerator& getInstance();
    Tuple generateTuple();

    TuplePattern generateTuplePattern();
};


#endif //UXP1A_TUPLEGENERATOR_H
