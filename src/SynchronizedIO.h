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

    SynchronizedIO();

    SynchronizedIO( const SynchronizedIO & )=delete;

    SynchronizedIO& operator=(const SynchronizedIO&)=delete;

public:

    static SynchronizedIO & getInstance()
    {
        static SynchronizedIO instance;
        return instance;
    }

    void print(std::string toPrint, Color color);

};

#endif //SYNCHRONIZEDIO_H
