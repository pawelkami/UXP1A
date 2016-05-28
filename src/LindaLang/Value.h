
#ifndef UXP1A_VALUE_H
#define UXP1A_VALUE_H

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>



class Value
{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {

    }
public:
    virtual ~Value();
};

typedef boost::shared_ptr<Value> PValue;

#endif //UXP1A_VALUE_H
