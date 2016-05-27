//
// Created by tomasz on 5/27/16.
//

#ifndef UXP1A_DETAILEDVALUE_H
#define UXP1A_DETAILEDVALUE_H

#include "Value.h"
#include <memory>
#include <string>

template<class T>
class DetailedValue: public Value
{
private:
    T value;
public:
    T getValue() const;

    void setValue(T val);

    std::string getTypeName();
    std::string getStrValue();
};


#endif //UXP1A_DETAILEDVALUE_H
