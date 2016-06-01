
#include "LindaLogger.h"
#include <chrono>
#include <zconf.h>

LindaLogger &LindaLogger::getInstance()
{
    static LindaLogger log;
    return log;
}

LindaLogger::LindaLogger()
{
}

LindaLogger::~LindaLogger()
{
    if(outFile.is_open())
        outFile.close();
}

void LindaLogger::log(Level level, const std::string &message, char const* function)
{
    openLogFile();
    std::string lvl;
    switch(level)
    {
        case ERROR:
            lvl = " ERROR: ";
            break;

        case WARNING:
            lvl = " WARNING: ";
            break;

        case INFO:
            lvl = " INFO: ";
            break;

        case DEBUG:
            lvl = " DEBUG: ";
            break;
    }
    char humanTime[20];
    std::time_t now = time(nullptr);
    std::strftime(humanTime, sizeof(humanTime), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    outFile << humanTime << lvl << " pid " <<  getpid() << " " << function << "() " << message << '\n';
    outFile.close();
}

void LindaLogger::openLogFile()
{
    outFile.open(LOGFILENAME, std::ios::out | std::ios::app);
}
