#include <src/LindaLang/TupleGenerator.h>
#include "Client.h"


const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");


Client::Client()
{
}

Client::Client(const Pipe &pResponse, const Pipe &pRequest) : linda(Linda(pResponse, pRequest))
{
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
            Tuple tuple = TUPLE_GENERATOR.generateTuple();

            if(linda.output(tuple))
                std::cout << green <<"client pid: " << getpid() << " sent tuple " << tuple.toString() << std::endl;
        }
        else
        {
            TuplePattern pattern = TUPLE_GENERATOR.generateTuplePattern();
            Tuple tuple;
            if(dist(rd))
            {
                std::cout << green << "client pid: " << getpid() << " sent TuplePattern to read" << pattern.toString().c_str() << std::endl;
                if(linda.read(pattern, 2, tuple))
                {
                    std::cout <<  green << "client pid: " << getpid() << " received Tuple " << tuple.toString() << std::endl;
                }

            }
            else
            {
                std::cout << green << "client pid: " << getpid() << " sent TuplePattern to input" << pattern.toString().c_str() << std::endl;
                if(linda.input(pattern, 2, tuple))
                {
                    std::cout << green << "client pid: " << getpid() << " received Tuple " << tuple.toString() << std::endl;
                }
            }
        }

//        struct timeval tv;
//        tv.tv_sec = dist(rd) % 3;
//
//        // pauzujemy
//        select(0, nullptr, nullptr, nullptr, &tv);

    }
}






