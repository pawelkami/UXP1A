#include <iostream>
#include <src/LindaLang/Pipe.h>
#include <map>
#include <src/client/Client.h>
#include <src/server/Server.h>

using namespace std;

int main()
{
    map<pid_t, Pipe> mapa;
    Pipe pipeRequest;

    for(int i = 0; i < 5; ++i)
    {
        Pipe pipe;
        int ret;

        if((ret = fork()) == 0)
        {
            Client client(pipe, pipeRequest);
            client.run();
        }

        mapa[ret] = pipe;

    }
    Server serv(pipeRequest);
    serv.setPipes(mapa);
    serv.processRequests();

    return 0;
}