#include "SynchronizedIO.h"

SynchronizedIO::SynchronizedIO()
{
    sem_init(&sem, 1, 1);
    colorMap[Color::RED] = std::string("\033[0;31m");
    colorMap[Color::GREEN] = std::string("\033[1;32m");
    colorMap[Color::YELLOW] = std::string("\033[1;33m");
    colorMap[Color::CYAN] = std::string("\033[0;36m");
    colorMap[Color::MAGENTA] = std::string("\033[0;35m");
    colorMap[Color::RESET] = std::string("\033[0m");
}

void SynchronizedIO::print(std::string toPrint, Color color)
{
    sem_wait(&sem);
    std::cout << colorMap[color] << toPrint << std::endl;
    sem_post(&sem);
}