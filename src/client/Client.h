
#ifndef UXP1A_CLIENT_H
#define UXP1A_CLIENT_H

#include <chrono>
#include <cstdint>
#include <random>
#include "LindaLang/Tuple.h"

#include <functional>
#include <src/LindaLang/Pipe.h>
#include <src/LindaLang/Linda.h>


#define MIN_TUPLE_LENGTH 2
#define MAX_TUPLE_LENGTH 4
#define MAXSTRLEN 20

class Client
{
public:

    Client();

    Linda linda;

    Client(const Pipe& pRequest, const Pipe& pResponse);

    void run();
private:
    std::vector<std::function<TupleValue ()> > tupleGenerator;

    std::vector<std::function<TuplePatternValue ()> > tuplePatternGenerator;

    void init();

    Tuple generateTuple();

    TuplePattern generateTuplePattern();

    int generateInt();

    float generateFloat();

    std::string generateString();

    TupleValue generateStringTuple();

    TupleValue generateIntTuple();

    TupleValue generateFloatTuple();

    TuplePatternValue generateIntTuplePattern();

    TuplePatternValue generateFloatTuplePattern();

    TuplePatternValue generateStringTuplePattern();
};


#endif //UXP1A_CLIENT_H
