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
    std::string filename = "client" + std::to_string(getpid()) + ".log";
    logger.init(filename);
}


void Client::run()
{
    logger.pushLog("connected");
    std::cout << red << "client pid: " << std::to_string(getpid()) << " connected" << std::endl;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 1);

    while(true)
    {
        if(dist(rd))
        {
            Tuple tuple = TUPLE_GENERATOR.generateTuple();

            if(linda.output(tuple))
            {
                logger.pushLog("sent tuple " + tuple.toString());
                std::cout << magenta << std::string("client pid: " + std::to_string(getpid()) + " sent tuple " + tuple.toString()) << reset << std::endl;
            }
        }
        else
        {
            TuplePattern pattern = TUPLE_GENERATOR.generateTuplePattern();
            Tuple tuple;
            if(dist(rd))
            {
                logger.pushLog("sent TuplePattern to read " + pattern.toString());
                std::cout << magenta << std::string("client pid: " + std::to_string(getpid()) + " sent TuplePattern to read " + pattern.toString().c_str()) << reset << std::endl;

                if(linda.read(pattern, 2, tuple))
                {
                    logger.pushLog("received Tuple " + tuple.toString());
                    std::cout << magenta << std::string("client pid: " + std::to_string(getpid()) + " received Tuple " + tuple.toString()) << reset << std::endl;
                }

            }
            else
            {
                logger.pushLog("sent TuplePattern to input" + pattern.toString());
                std::cout << magenta << std::string("client pid: " + std::to_string(getpid()) + " sent TuplePattern to input" + pattern.toString().c_str()) << reset << std::endl;

                if(linda.input(pattern, 2, tuple))
                {
                    logger.pushLog("received Tuple " + tuple.toString());
                    std::cout << magenta << std::string("client pid: " + std::to_string(getpid()) + " received Tuple " + tuple.toString()) << reset << std::endl;
                }
            }
        }
    }
}


Client::~Client()
{
    logger.close();
}



