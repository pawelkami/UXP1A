#ifndef SYNCHRONIZEDIO_H
#define SYNCHRONIZEDIO_H

#include <semaphore.h>
#include <string>
#include <iostream>
#include <map>

enum class Color :unsigned
{
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    CYAN = 4,
    MAGENTA = 5,
    RESET = 6,
};

class SynchronizedIO
{
private:

    std::map<Color, std::string> colorMap;

    sem_t sem;

public:

    SynchronizedIO();
    SynchronizedIO( const SynchronizedIO & ) { }

    void print(std::string toPrint, Color color);

};

#endif //SYNCHRONIZEDIO_H
