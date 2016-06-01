
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

    std::map<pid_t, Pipe> pipesResponse;

    void processMessage(const Message& msg);
public:

    Server(const Pipe& p);

    ~Server();

    void processRequests();

    void addPipe(pid_t pid, const Pipe& pipe);

    void setPipes(std::map<pid_t, Pipe> pipes);

    void addTuple(const Tuple& tuple);


};


#endif //UXP1A_SERVER_H
