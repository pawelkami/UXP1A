
#include "TupleGenerator.h"

TupleGenerator::TupleGenerator()
{
    init();
}

void TupleGenerator::init()
{
    this->tupleGenerator.push_back(std::bind(&TupleGenerator::generateIntTuple, this));
    this->tupleGenerator.push_back(std::bind(&TupleGenerator::generateFloatTuple, this));
    this->tupleGenerator.push_back(std::bind(&TupleGenerator::generateStringTuple, this));
    this->tuplePatternGenerator.push_back(std::bind(&TupleGenerator::generateIntTuplePattern, this));
    this->tuplePatternGenerator.push_back(std::bind(&TupleGenerator::generateFloatTuplePattern, this));
    this->tuplePatternGenerator.push_back(std::bind(&TupleGenerator::generateStringTuplePattern, this));
}

TupleValue TupleGenerator::generateIntTuple()
{
    return TupleValue(generateInt());
}

TupleValue TupleGenerator::generateFloatTuple()
{
    return TupleValue(generateFloat());
}

TupleValue TupleGenerator::generateStringTuple()
{
    return TupleValue(generateString());
}

TuplePatternValue TupleGenerator::generateIntTuplePattern()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, static_cast<unsigned int>(Condition::SIZE) - 1);
    return TuplePatternValue(generateInt(), static_cast<Condition>(dist(rd)));
}

TuplePatternValue TupleGenerator::generateFloatTuplePattern()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, static_cast<unsigned int>(Condition::SIZE) - 1);
    return TuplePatternValue(generateFloat(), static_cast<Condition>(dist(rd)));
}

TuplePatternValue TupleGenerator::generateStringTuplePattern()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, static_cast<unsigned int>(Condition::SIZE) - 1);
    Condition cond = static_cast<Condition>(dist(rd));
    return TuplePatternValue(cond != Condition::ANY ? generateString() : "", cond);
}

Tuple TupleGenerator::generateTuple()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, std::numeric_limits<unsigned int>::max());

    unsigned int tupleLength = MIN_TUPLE_LENGTH + (dist(rd) % (MAX_TUPLE_LENGTH - MIN_TUPLE_LENGTH + 1));

    std::vector<TupleValue> tuples;

    for(auto it = 0; it < tupleLength; ++it)
        tuples.push_back(this->tupleGenerator[dist(rd) % 3]());

    return Tuple(tuples);
}

TuplePattern TupleGenerator::generateTuplePattern()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, std::numeric_limits<unsigned int>::max());

    unsigned int tuplePatternLength = MIN_TUPLE_LENGTH + (dist(rd) % (MAX_TUPLE_LENGTH - MIN_TUPLE_LENGTH + 1));

    std::vector<TuplePatternValue> tuplePaterns;

    for(auto it = 0; it < tuplePatternLength; ++it)
        tuplePaterns.push_back(this->tuplePatternGenerator[dist(rd) % 3]());

    return TuplePattern(tuplePaterns);
}

int TupleGenerator::generateInt()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, std::numeric_limits<int>::max());

    int valInt = dist(rd);
    (dist(rd) % 2 ? valInt *= (-1) : valInt);
    return valInt;
}

float TupleGenerator::generateFloat()
{
    std::random_device rd;
    std::uniform_real_distribution<float> dist(-FLOAT_IN_TUPLE_MAX, FLOAT_IN_TUPLE_MAX);
    std::uniform_int_distribution<int> distBinary(0, 1);

    float valFlt = dist(rd);
    (distBinary(rd) ? valFlt *= (-1) : valFlt);
    return valFlt;
}

std::string TupleGenerator::generateString()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, MAXSTRLEN);
    std::string randStr = "";
    auto len = dist(rd);
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i)
        randStr += alphanum[dist(rd) % (sizeof(alphanum) - 1)];
    return randStr;
}

TupleGenerator &TupleGenerator::getInstance()
{
    static TupleGenerator generator;
    return generator;
}


