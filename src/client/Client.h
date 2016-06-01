
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
private:

    Linda linda;

public:
    Client();

    void run();

    Client(const Pipe& pRequest, const Pipe& pResponse);
};


#endif //UXP1A_CLIENT_H
