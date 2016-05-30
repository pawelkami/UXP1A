
#ifndef UXP1A_SERVER_H
#define UXP1A_SERVER_H


#include "LindaLang/Pipe.h"
#include <map>
#include "TupleSpace.h"

class Server
{
private:
    TupleSpace tupleSpace;

    Pipe pipeRequest;

    std::map<pid_t, Pipe> pipesResponse;

    void processMessage(const Message& msg);
public:

    Server(const Pipe& p);

    void processRequests();

    void addPipe(pid_t pid, const Pipe& pipe);

    void setPipes(std::map<pid_t, Pipe> pipes);




};


#endif //UXP1A_SERVER_H
