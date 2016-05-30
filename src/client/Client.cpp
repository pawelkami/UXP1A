#include "Client.h"

Client::Client()
{
    init();
}

Client::Client(const Pipe &pResponse, const Pipe &pRequest) : linda(Linda(pResponse, pRequest))
{
    init();
}

void Client::init()
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
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, static_cast<unsigned int>(Condition::SIZE));
    return TuplePatternValue(generateInt(), static_cast<Condition>(dist(rd)));
}

TuplePatternValue Client::generateFloatTuplePattern()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, static_cast<unsigned int>(Condition::SIZE));
    return TuplePatternValue(generateFloat(), static_cast<Condition>(dist(rd)));
}

TuplePatternValue Client::generateStringTuplePattern()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, static_cast<unsigned int>(Condition::SIZE));
    return TuplePatternValue(generateString(), static_cast<Condition>(dist(rd)));
}

Tuple Client::generateTuple()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, std::numeric_limits<unsigned int>::max());

    unsigned int tupleLength = MIN_TUPLE_LENGTH + (dist(rd) % (MAX_TUPLE_LENGTH - MIN_TUPLE_LENGTH + 1));

    std::vector<TupleValue> tuples;

    for(auto it = 0; it < tupleLength; ++it)
        tuples.push_back(this->tupleGenerator[dist(rd) % 3]());

    return Tuple(tuples);
}

TuplePattern Client::generateTuplePattern()
{
    std::random_device rd;
    std::uniform_int_distribution<unsigned int> dist(0, std::numeric_limits<unsigned int>::max());

    unsigned int tuplePatternLength = MIN_TUPLE_LENGTH + (dist(rd) % (MAX_TUPLE_LENGTH - MIN_TUPLE_LENGTH + 1));

    std::vector<TuplePatternValue> tuplePaterns;

    for(auto it = 0; it < tuplePatternLength; ++it)
        tuplePaterns.push_back(this->tuplePatternGenerator[dist(rd) % 3]());

    return TuplePattern(tuplePaterns);
}

int Client::generateInt()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, std::numeric_limits<int>::max());

    int valInt = dist(rd);
    (dist(rd) % 2 ? valInt *= (-1) : valInt);
    return valInt;
}

float Client::generateFloat()
{
    std::random_device rd;
    std::uniform_real_distribution<float> dist(-FLOAT_IN_TUPLE_MAX, FLOAT_IN_TUPLE_MAX);
    std::uniform_int_distribution<int> distBinary(0, 1);

    float valFlt = dist(rd);
    (distBinary(rd) ? valFlt *= (-1) : valFlt);
    return valFlt;
}

std::string Client::generateString()
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


void Client::run()
{
    std::cout << "client pid: " << getpid() << " connected" << std::endl;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 1);

    while(true)
    {
        if(dist(rd))
        {
            Tuple tuple = generateTuple();

            if(linda.output(tuple))
                std::cout << "client pid: " << getpid() << " sent tuple " << tuple.toString() << std::endl;
        }
        else
        {
            TuplePattern pattern = generateTuplePattern();
            Tuple tuple;
            if(dist(rd))
            {
                if(linda.read(pattern, 2, tuple))
                {
                    std::cout << "client pid: " << getpid() << " sent TuplePattern to read" << pattern.toString() << std::endl;
                    std::cout << "client pid: " << getpid() << " received Tuple " << tuple.toString() << std::endl;
                }

            }
            else
            {
                if(linda.input(pattern, 2, tuple))
                {
                    std::cout << "client pid: " << getpid() << " sent TuplePattern to input" << pattern.toString() << std::endl;
                    std::cout << "client pid: " << getpid() << " received Tuple " << tuple.toString() << std::endl;
                }
            }
        }

        struct timeval tv;
        tv.tv_sec = dist(rd) % 3;

        // pauzujemy
        select(0, nullptr, nullptr, nullptr, &tv);

    }
}






