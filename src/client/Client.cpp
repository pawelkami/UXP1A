#include "Client.h"

Client::Client()
{
    this->tupleGenerator.push_back(std::bind(&Client::generateIntTuple));
    this->tupleGenerator.push_back(std::bind(&Client::generateFloatTuple));
    this->tupleGenerator.push_back(std::bind(&Client::generateStringTuple));
}

Tuple Client::generateIntTuple()
{
    return Tuple();
}


Tuple Client::generateFloatTuple()
{
    return Tuple();
}

Tuple Client::generateStringTuple()
{
    return Tuple();
}

Tuple Client::generateTuple()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);

    std::uint8_t tupleLength = MIN_LENGTH + (gen() % (MAX_LENGTH - MIN_LENGTH + 1));

    std::vector<TupleValue> tuples;

    for(auto it = 0; it < tupleLength; ++it)
    {
        Tuple tup = this->tupleGenerator[gen()%3]();
        /*
        switch(gen() % 3)
        {
            case 0: // string
                
                break;
            case 1: // int

                break;
            case 2: // float

                break;
        }
         */
    }

    return Tuple(tuples);
}

TuplePattern Client::generateTuplePattern()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);

    std::uint8_t tuplePatternLength = MIN_LENGTH + (gen() % (MAX_LENGTH - MIN_LENGTH + 1));

    for(auto it = 0; it < tuplePatternLength; ++it)
    {

    }
}