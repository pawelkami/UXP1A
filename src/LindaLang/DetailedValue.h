
#ifndef UXP1A_DETAILEDVALUE_H
#define UXP1A_DETAILEDVALUE_H

#include "Value.h"
#include <memory>
#include <string>
#include <boost/serialization/base_object.hpp>


template<class T>
class DetailedValue: public Value
{
private:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        //ar & boost::serialization::base_object(*this);
        ar & value;
    }

    T value;
public:
    T getValue() const;

    void setValue(T val);

    std::string getTypeName();
    std::string getStrValue();
};

template class DetailedValue<int>;
template class DetailedValue<std::string>;
template class DetailedValue<float>;

#endif //UXP1A_DETAILEDVALUE_H
