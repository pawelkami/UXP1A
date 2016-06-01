
#ifndef UXP1A_SERVER_H
#define UXP1A_SERVER_H

#include "LindaLang/Pipe.h"
#include <map>
#include "TupleSpace.h"
#include "Logger.h"

class Server
{
private:
    TupleSpace tupleSpace;

    Logger logger;

    Pipe pipeRequest;

    void processMessage(const Message& msg);

    static std::map<pid_t, Pipe> pipesResponse;
public:

    Server(const Pipe& p);

    ~Server();

    void processRequests();

    void addPipe(pid_t pid, const Pipe& pipe);

    void setPipes(std::map<pid_t, Pipe> pipes);

    void addTuple(const Tuple& tuple);

    static void sigchldHandler(int sig);
};


#endif //UXP1A_SERVER_H
