//
// Created by tomasz on 6/1/16.
//

#include "Logger.h"

Logger::Logger()
{
    doLog = [this] (const std::string& log) {};
}

Logger::Logger(const std::string& filename)
{
    init(filename);
}

void Logger::init(const std::string& filename)
{
    doLog = [this] (const std::string& log) {};
    logFile.open(filename.c_str(), std::ios::out);
    if(logFile.is_open())
    {
        doLog = [this] (const std::string& log)
        {
            char humanTime[20];
            std::time_t now = time(nullptr);
            std::strftime(humanTime, sizeof(humanTime), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            logFile << humanTime << ": " << log << std::endl;
        };
    }
}

void Logger::pushLog(const std::string& log)
{
    doLog(log);
}

void Logger::close()
{
    logFile.close();
}