
#ifndef UXP1A_CLIENT_H
#define UXP1A_CLIENT_H

#include <chrono>
#include <cstdint>
#include <random>
#include "../LindaLang/Tuple.h"


#define MIN_LENGTH 2
#define MAX_LENGTH 4

typedef std::independent_bits_engine<std::mt19937, 64, std::uint_fast64_t> generatorType;

class Client
{
public:

    Client();

private:

    Tuple generateTuple();

    TuplePattern generateTuplePattern();

};


#endif //UXP1A_CLIENT_H
