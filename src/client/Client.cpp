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
    return TupleValue(generateInt());
}

TupleValue Client::generateFloatTuple()
{
    return TupleValue(generateFloat());
}

TupleValue Client::generateStringTuple()
{
    return TupleValue(generateString());
}

TuplePatternValue Client::generateIntTuplePattern()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);
    return TuplePatternValue(generateInt(), static_cast<Condition>(gen() % 6));
}

TuplePatternValue Client::generateFloatTuplePattern()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);
    return TuplePatternValue(generateFloat(), static_cast<Condition>(gen() % 6));
}

TuplePatternValue Client::generateStringTuplePattern()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);
    return TuplePatternValue(generateString(), static_cast<Condition>(gen() % 6));
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

    return TuplePattern(tuplePaterns);
}

int Client::generateInt()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);
    int valInt = gen() % INT_MAX;
    (gen() % 2 ? valInt *= (-1) : valInt);
    return valInt;
}

float Client::generateFloat()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);
    float valFlt = static_cast<float>(gen()) / static_cast<float>(gen.max())/FLT_MAX;
    (gen() % 2 ? valFlt *= (-1) : valFlt);
    return valFlt;
}

std::string Client::generateString()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generatorType gen(seed);
    std::string randStr = "";
    auto len = gen() % MAXSTRLEN;
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i)
        randStr += alphanum[gen() % (sizeof(alphanum) - 1)];
    return randStr;
}

Client::Client(const Pipe &pResponse, const Pipe &pRequest) : linda(Linda(pResponse, pRequest))
{
}

void Client::run()
{
    while(true)
    {
        std::cout << "client: " << getpid() << std::endl;
    }
}



