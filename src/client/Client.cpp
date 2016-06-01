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

Client::Client(const Pipe &pResponse, const Pipe &pRequest, SynchronizedIO& console) : linda(Linda(pResponse, pRequest)), console(console)
{
}




void Client::run()
{
    std::cout << "\033[0;31m" << "aaa" << std::endl;
    console.print("client pid: " + std::to_string(getpid()) + " connected", Color::RED);
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 1);

    while(true)
    {
        if(dist(rd))
        {
            Tuple tuple = TUPLE_GENERATOR.generateTuple();

            if(linda.output(tuple))
                console.print(std::string("client pid: " + std::to_string(getpid()) + " sent tuple " + tuple.toString()), Color::GREEN);
        }
        else
        {
            TuplePattern pattern = TUPLE_GENERATOR.generateTuplePattern();
            Tuple tuple;
            if(dist(rd))
            {
                console.print(std::string("client pid: " + std::to_string(getpid()) + " sent TuplePattern to read " + pattern.toString().c_str()), Color::GREEN);

                if(linda.read(pattern, 2, tuple))
                {
                    console.print(std::string("client pid: " + std::to_string(getpid()) + " received Tuple " + tuple.toString()), Color::GREEN);
                }

            }
            else
            {
                console.print(std::string("client pid: " + std::to_string(getpid()) + " sent TuplePattern to input" + pattern.toString().c_str()), Color::GREEN);

                if(linda.input(pattern, 2, tuple))
                {
                    console.print(std::string("client pid: " + std::to_string(getpid()) + " received Tuple " + tuple.toString()), Color::GREEN);
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






