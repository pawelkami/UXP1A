
#ifndef UXP1A_LINDA_H
#define UXP1A_LINDA_H


#include <ctime>
#include "Tuple.h"
#include "TuplePattern.h"
#include "Pipe.h"
#include "Message.h"

/**
 * Klasa umożliwiająca pobieranie oraz dodawanie krotek do przestrzeni krotek.
 */
class Linda
{
private:
    Pipe pipeRequest;
    Pipe pipeResponse;

    bool sendAndReceiveResponse(const Message& msg, unsigned timeout, Tuple& returnTuple);

    bool sendMsg(const Message& msg);

    bool receiveMsg(unsigned timeout, Tuple& returnTuple);
public:
    Linda();

    Linda(const Pipe& pipeResponse, const Pipe& pipeRequest);

    bool output(const Tuple& tuple);

    bool read(const TuplePattern& pattern, unsigned timeout, Tuple& returnTuple);

    bool input(const TuplePattern& pattern, unsigned timeout, Tuple& returnTuple);

};


#endif //UXP1A_LINDA_H
