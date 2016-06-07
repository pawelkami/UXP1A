#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Linda.h"
#include "Message.h"
#include "LindaLogger.h"

Linda::~Linda()
{
    pipeRequest.closeDescriptors();
    pipeResponse.closeDescriptors();
}

bool Linda::output(const Tuple& tuple)
{
    LOG_DEBUG("entry: " + tuple.toString());
    Message msg(OperationType::OUTPUT, tuple);

    return sendMsg(msg);
}

bool Linda::read(const TuplePattern &pattern, unsigned timeout, Tuple &returnTuple)
{
    LOG_DEBUG("entry: " + pattern.toString() + " timeout: " + std::to_string(timeout));

    Message msg(OperationType::READ, pattern);
    time_t tval;
    time(&tval);
    msg.setTimeout(tval + timeout);

    return sendAndReceiveResponse(msg, timeout, returnTuple);
}

bool Linda::input(const TuplePattern &pattern, unsigned timeout, Tuple &returnTuple)
{
    LOG_DEBUG("entry: " + pattern.toString() + " timeout: " + std::to_string(timeout));
    Message msg(OperationType::INPUT, pattern);
    time_t tval;
    time(&tval);
    msg.setTimeout(tval + timeout);

    return sendAndReceiveResponse(msg, timeout, returnTuple);
}

Linda::Linda(const Pipe &pipeResponse, const Pipe &pipeRequest)
{
    LOG_DEBUG("");

    this->pipeResponse = pipeResponse;
    this->pipeRequest = pipeRequest;
}

bool Linda::sendAndReceiveResponse(const Message &msg, unsigned timeout, Tuple &returnTuple)
{
    if(!sendMsg(msg))
    {
        LOG_WARNING("sendMsg did not complete successfully");
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
        // wysłanie wiadomości przez pipe
        pipeRequest.writePipe(ss.str().c_str(), ss.str().size());
    }
    catch(std::exception& ex)
    {
        LOG_ERROR(ex.what());
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
        LOG_INFO("Timeout occurred");
        // zwracamy nieudaną próbę
        return false;
    }

    return true;
}

Linda::Linda()
{

}
















