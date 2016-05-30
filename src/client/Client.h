
#ifndef UXP1A_CLIENT_H
#define UXP1A_CLIENT_H

#include <chrono>
#include <cstdint>
#include <random>
#include <climits>
#include <cfloat>
#include "../LindaLang/Tuple.h"

#include <functional>


#define MIN_LENGTH 2
#define MAX_LENGTH 4
#define MAXSTRLEN 20

typedef std::independent_bits_engine<std::mt19937, 64, std::uint_fast64_t> generatorType;

class Client
{
public:

    Client();

private:
    std::vector<std::function<TupleValue ()> > tupleGenerator;

    std::vector<std::function<TuplePatternValue ()> > tuplePatternGenerator;

    Tuple generateTuple();

    TuplePattern generateTuplePattern();

    std::string genRandomString(const int len);

    TupleValue generateStringTuple();

    TupleValue generateIntTuple();

    TupleValue generateFloatTuple();

    TuplePatternValue generateIntTuplePattern();

    TuplePatternValue generateFloatTuplePattern();

    TuplePatternValue generateStringTuplePattern();
};


#endif //UXP1A_CLIENT_H
