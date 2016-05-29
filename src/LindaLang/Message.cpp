
#include "Message.h"

OperationType Message::getOperationType() const
{
    return opType;
}

void Message::setOperationType(OperationType type)
{
    opType = type;
}

Message::Message()
{
}

Message::Message(OperationType type)
{
    opType = type;
}

Message::Message(OperationType type, Tuple tuple)
{
    opType = type;
    value = tuple;
}

Message::Message(OperationType type, TuplePattern pattern)
{
    opType = type;
    value = pattern;
}

time_t Message::getTimeout()
{
    return timeout;
}

void Message::setTimeout(time_t timeout)
{
    this->timeout = timeout;
}















