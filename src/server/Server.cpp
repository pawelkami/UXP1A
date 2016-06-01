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
            tupleSpace.insertTuple(boost::get<Tuple>(msg.value));
            console.print(std::string("server pid: " + std::to_string(getpid()) + " received Tuple " + boost::get<Tuple>(msg.value).toString()), Color::MAGENTA);
            break;

        case OperationType::INPUT:
        case OperationType::READ:
            Tuple tuple;
            console.print(std::string("server pid: " + std::to_string(getpid()) + " received TuplePattern " + boost::get<TuplePattern>(msg.value).toString().c_str()), Color::MAGENTA);

            if(tupleSpace.getTuple(boost::get<TuplePattern>(msg.value), tuple))
            {
                console.print(std::string("found tuple " + tuple.toString()), Color::MAGENTA);


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
                        tupleSpace.removeTuple(boost::get<TuplePattern>(msg.value));
                    }

                }
                console.print(std::string("server pid: " + std::to_string(getpid()) + " sent Tuple " + tuple.toString()), Color::MAGENTA);

            }
            break;

    }
}

Server::Server(const Pipe &p, SynchronizedIO& console) : console(console)
{
    pipeRequest = p;
}

void Server::addPipe(pid_t pid, const Pipe& pipe)
{
    pipesResponse[pid] = pipe;
}

void Server::setPipes(std::map<pid_t, Pipe> pipes)
{
    this->pipesResponse = pipes;
}

void Server::addTuple(const Tuple& tuple)
{
    tupleSpace.insertTuple(tuple);
}

void Server::setConsole(const SynchronizedIO &console)
{
    this->console = console;
}







