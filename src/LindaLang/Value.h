
#ifndef UXP1A_VALUE_H
#define UXP1A_VALUE_H

#include <boost/shared_ptr.hpp>

class Value
{
public:
    virtual ~Value();
};

typedef boost::shared_ptr<Value> PValue;

#endif //UXP1A_VALUE_H
