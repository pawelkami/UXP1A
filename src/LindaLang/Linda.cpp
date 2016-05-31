#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Linda.h"
#include "Message.h"

Linda::~Linda()
{
    pipeRequest.closedDescriptors();
    pipeResponse.closedDescriptors();
}

bool Linda::output(const Tuple& tuple)
{
    Message msg(OperationType::OUTPUT, tuple);

    return sendMsg(msg);
}

bool Linda::read(const TuplePattern &pattern, unsigned timeout, Tuple &returnTuple)
{
    Message msg(OperationType::READ, pattern);
    time_t tval;
    time(&tval);
    msg.setTimeout(tval + timeout);

    return sendAndReceiveResponse(msg, timeout, returnTuple);
}

bool Linda::input(const TuplePattern &pattern, unsigned timeout, Tuple &returnTuple)
{
    Message msg(OperationType::INPUT, pattern);
    time_t tval;
    time(&tval);
    msg.setTimeout(tval + timeout);

    return sendAndReceiveResponse(msg, timeout, returnTuple);
}

Linda::Linda(const Pipe &pipeResponse, const Pipe &pipeRequest)
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

    try
    {
        // czekamy tak długo aż pipe nie zostanie opróżniony
//        while(pipeRequest.checkReadingAvailibility(DEFAULT_TIMEOUT));

        // wysłanie wiadomości przez pipe
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
    // sprawdzamy czy jest coś w potoku do odczytania
    if(pipeResponse.checkReadingAvailibility(timeout))
    {
        std::unique_ptr<char> readBuf(new char[PIPE_BUF]);
        memset(readBuf.get(), 0, PIPE_BUF);

        // czytamy
        try
        {
            pipeResponse.readPipe(readBuf.get(), PIPE_BUF);
        }
        catch(std::exception& ex)
        {
            return false;
        }

        std::stringstream is;
        is << readBuf.get();

        boost::archive::text_iarchive ia(is);
        // zapisujemy wynik
        ia >> returnTuple;
    }
    else
    {
        // zwracamy nieudaną próbę
        return false;
    }

    return true;
}

Linda::Linda()
{

}
















