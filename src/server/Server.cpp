#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "LindaLang/Message.h"
#include "Server.h"
#include <boost/variant/get.hpp>


const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");


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
            std::cout << cyan << "server pid: " << getpid() << " received Tuple " << boost::get<Tuple>(msg.value).toString() << std::endl;
            break;

        case OperationType::INPUT:
        case OperationType::READ:
            Tuple tuple;
            std::cout << cyan << "server pid: " << getpid() << " received TuplePattern " << boost::get<TuplePattern>(msg.value).toString().c_str() << std::endl;
            if(tupleSpace.getTuple(boost::get<TuplePattern>(msg.value), tuple))
            {
                std::cout << cyan << "found tuple " << tuple.toString() << std::endl;

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
                std::cout << cyan << "server pid: " << getpid() << " sent Tuple " << tuple.toString() << std::endl;

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

void Server::setPipes(std::map<pid_t, Pipe> pipes)
{
    this->pipesResponse = pipes;
}

void Server::addTuple(const Tuple& tuple)
{
    tupleSpace.insertTuple(tuple);
}





