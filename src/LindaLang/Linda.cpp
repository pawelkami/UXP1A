#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Linda.h"
#include "Message.h"

bool Linda::output(const Tuple& tuple)
{
    Message msg(OperationType::OUTPUT, tuple);

    return sendMsg(msg);
}

bool Linda::read(const TuplePattern &pattern, unsigned timeout, Tuple &returnTuple)
{
    Message msg(OperationType::READ, pattern);

    return sendAndReceiveResponse(msg, timeout, returnTuple);
}

bool Linda::input(const TuplePattern &pattern, unsigned timeout, Tuple &returnTuple)
{
    Message msg(OperationType::INPUT, pattern);

    return sendAndReceiveResponse(msg, timeout, returnTuple);
}

Linda::Linda(Pipe &pipeResponse, Pipe &pipeRequest)
{
    this->pipeResponse = pipeResponse;
    this->pipeRequest = pipeRequest;
    //this->pipeResponse.closePipeEnd(PipeEnd::WriteEnd);
    //this->pipeRequest.closePipeEnd(PipeEnd::ReadEnd);
}

bool Linda::sendAndReceiveResponse(const Message &msg, unsigned timeout, Tuple &returnTuple)
{
    if(!sendMsg(msg))
    {
        return false;
    }
    return receiveMsg(timeout, returnTuple);
}

bool Linda::sendMsg(const Message &msg)
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);

    // zapisujemy wiadomość do strumienia
    oa << msg;

    // wysłanie wiadomości przez pipe
    try
    {
        pipeRequest.writePipe(ss.str().c_str(), ss.str().size());
    }
    catch(std::exception& ex)
    {
        return false;
    }

    return true;
}

bool Linda::receiveMsg(unsigned timeout, Tuple &returnTuple)
{
    if(pipeResponse.checkReadingAvailibility(timeout))
    {
        std::unique_ptr<char> readBuf(new char[PIPE_BUF]);
        memset(readBuf.get(), 0, PIPE_BUF);

        pipeResponse.readPipe(readBuf.get(), PIPE_BUF);
        std::stringstream is;
        is << readBuf.get();

        boost::archive::text_iarchive ia(is);

        ia >> returnTuple;
    }
    else
    {
        return false;
    }

    return true;
}














