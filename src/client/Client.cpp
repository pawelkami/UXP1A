#include "Client.h"

Client::Client()
{
    this->tupleGenerator.push_back(std::bind(&Client::generateIntTuple, this));
    this->tupleGenerator.push_back(std::bind(&Client::generateFloatTuple, this));
    this->tupleGenerator.push_back(std::bind(&Client::generateStringTuple, this));
    this->tuplePatternGenerator.push_back(std::bind(&Client::generateIntTuplePattern, this));
    this->tuplePatternGenerator.push_back(std::bind(&Client::generateFloatTuplePattern, this));
    this->tuplePatternGenerator.push_back(std::bind(&Client::generateStringTuplePattern, this));
}

TupleValue Client::generateIntTuple()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);
    int valInt = gen() % INT_MAX;
    (gen() % 2 ? valInt *= (-1) : valInt);
    return TupleValue(valInt);
}


TupleValue Client::generateFloatTuple()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);
    float valFlt = static_cast<float>(gen()) / static_cast<float>(gen.max())/FLT_MAX;
    (gen() % 2 ? valFlt *= (-1) : valFlt);
    return TupleValue(valFlt);
}

TupleValue Client::generateStringTuple()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);
    return TupleValue(genRandomString(gen() % MAXSTRLEN));
}

TuplePatternValue Client::generateIntTuplePattern()
{
    return TuplePatternValue();
}

TuplePatternValue Client::generateFloatTuplePattern()
{
    return TuplePatternValue();
}

TuplePatternValue Client::generateStringTuplePattern()
{
    return TuplePatternValue();
}

Tuple Client::generateTuple()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);

    std::uint8_t tupleLength = MIN_LENGTH + (gen() % (MAX_LENGTH - MIN_LENGTH + 1));

    std::vector<TupleValue> tuples;

    for(auto it = 0; it < tupleLength; ++it)
        tuples.push_back(this->tupleGenerator[gen()%3]());

    return Tuple(tuples);
}

TuplePattern Client::generateTuplePattern()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);

    std::uint8_t tuplePatternLength = MIN_LENGTH + (gen() % (MAX_LENGTH - MIN_LENGTH + 1));

    std::vector<TuplePatternValue> tuplePaterns;

    for(auto it = 0; it < tuplePatternLength; ++it)
        tuplePaterns.push_back(this->tuplePatternGenerator[gen()%3]());

    return tuplePaterns;
}

std::string Client::genRandomString(const int len)
{
    srand(time(NULL));
    std::string randStr;
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i)
        randStr += alphanum[rand() % (sizeof(alphanum) - 1)];
    return randStr;
}