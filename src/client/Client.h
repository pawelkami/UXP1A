
#ifndef UXP1A_CLIENT_H
#define UXP1A_CLIENT_H

#include <chrono>
#include <cstdint>
#include <random>
#include "LindaLang/Tuple.h"
#include <functional>
#include <src/LindaLang/Pipe.h>
#include <src/LindaLang/Linda.h>



class Client
{
public:

    Client();

    Linda linda;

    Client(const Pipe& pRequest, const Pipe& pResponse);

    void run();

private:
    std::vector<std::function<TupleValue ()> > tupleGenerator;

    std::vector<std::function<TuplePatternValue ()> > tuplePatternGenerator;
};


#endif //UXP1A_CLIENT_H
