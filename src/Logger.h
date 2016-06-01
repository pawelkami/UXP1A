//
// Created by tomasz on 6/1/16.
//

#ifndef UXP1A_LOGGER_H
#define UXP1A_LOGGER_H

#include <fstream>
#include <string>
#include <functional>
#include <ctime>
#include <iostream>


class Logger
{
private:
    std::ofstream logFile;
    std::function<void (const std::string& log)> doLog = nullptr;
public:
    Logger();
    Logger(const std::string& filename);
    void init(const std::string& filename);
    void pushLog(const std::string& log);
    void close();
};

#endif //UXP1A_LOGGER_H
