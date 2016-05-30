#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "LindaLang/Message.h"
#include "Server.h"
#include <boost/variant/get.hpp>


void Server::processRequests()
{
    std::unique_ptr<char> buf(new char[PIPE_BUF]);

    while(true)
    {
        memset(buf.get(), 0 , PIPE_BUF);

        try
        {

            if(pipeRequest.readPipe(buf.get(), PIPE_BUF))
            {
                Message msg;

                std::stringstream ss;
                ss << buf.get();
                boost::archive::text_iarchive ia(ss);
                ia >> msg;

                processMessage(msg);
            }
        }
        catch(std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
            return;
        }
    }
}

void Server::processMessage(const Message &msg)
{
    switch(msg.getOperationType())
    {
        case OperationType::OUTPUT:
            tupleSpace.insertTuple(boost::get<Tuple&>(msg.value));
            break;

        case OperationType::INPUT:
        case OperationType::READ:
            Tuple tuple;
            if(tupleSpace.getTuple(boost::get<TuplePattern&>(msg.value), tuple))
            {
                std::stringstream ss;

                boost::archive::text_oarchive oa(ss);

                oa << tuple;

                // licznik czasu w tej chwili
                time_t tval;
                time(&tval);

                // jeśli nie minął timeout to wysyłamy
                if(tval < msg.getTimeout())
                {
                    pipesResponse[msg.getPid()].writePipe(ss.str().c_str(), ss.str().size());

                    if(msg.getOperationType() == OperationType::INPUT)
                    {
                        tupleSpace.removeTuple(boost::get<TuplePattern&>(msg.value));
                    }

                }
            }
            break;

    }
}

Server::Server(const Pipe &p)
{
    pipeRequest = p;
}

void Server::addPipe(pid_t pid, const Pipe& pipe)
{
    pipesResponse[pid] = pipe;
}

