#include <iostream>
#include <src/LindaLang/Pipe.h>
#include <map>
#include <src/client/Client.h>
#include <src/server/Server.h>
#include <sstream>

using namespace std;

int main()
{
    map<pid_t, Pipe> mapa;
    Pipe pipeRequest(0);

    for(int i = 0; i < 5; ++i)
    {
        ostringstream ss;
        ss << i;
        Pipe pipe(i + 1);
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