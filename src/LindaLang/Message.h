
#ifndef UXP1A_MESSAGE_H
#define UXP1A_MESSAGE_H

#include "TuplePattern.h"
#include "Tuple.h"
#include <boost/serialization/access.hpp>
#include <boost/variant.hpp>
#include <boost/serialization/variant.hpp>

enum class OperationType : unsigned
{
    OUTPUT,
    READ,
    INPUT
};

/**
 * Klasa reprezentująca wiadomość wysyłaną poprzez potok nienazwany.
 */
class Message
{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & opType;
        ar & timeout;
        ar & value;
        ar & processPid;
    }

    OperationType opType;

    time_t timeout;

    pid_t processPid;

public:
    boost::variant<Tuple, TuplePattern> value;

    Message();

    Message(OperationType type);

    Message(OperationType type, Tuple tuple);

    Message(OperationType type, TuplePattern pattern);

    OperationType getOperationType() const;

    void setOperationType(OperationType type);

    time_t getTimeout() const;

    void setTimeout(time_t timeout);

    pid_t getPid() const;
};


#endif //UXP1A_MESSAGE_H
