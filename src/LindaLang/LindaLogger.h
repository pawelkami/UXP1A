
#ifndef UXP1A_LINDALOGGER_H
#define UXP1A_LINDALOGGER_H


#include <string>
#include <fstream>

#define LOGFILENAME "linda.log"
#define LOGGER LindaLogger::getInstance()

#define LOG_ERROR(Message_) LOGGER.log(ERROR, Message_, __FUNCTION__)
#define LOG_INFO(Message_) LOGGER.log(INFO, Message_, __FUNCTION__)
#define LOG_WARNING(Message_) LOGGER.log(WARNING, Message_, __FUNCTION__)
#define LOG_DEBUG(Message_) LOGGER.log(DEBUG, Message_, __FUNCTION__)


enum Level
{
    ERROR,
    INFO,
    WARNING,
    DEBUG
};

class LindaLogger
{
private:
    LindaLogger();

    std::ofstream outFile;

    void openLogFile();
public:
    static LindaLogger& getInstance();

    ~LindaLogger();

    void log(Level level, const std::string& message, char const* function );

};

#endif //UXP1A_LINDALOGGER_H
