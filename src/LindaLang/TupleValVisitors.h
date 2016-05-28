
#ifndef UXP1A_TUPLEVALVISITORS_H
#define UXP1A_TUPLEVALVISITORS_H

#include <string>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/get.hpp>
#include "Enums.h"


class GetTypeNameVis: public boost::static_visitor<std::string>
{
public:
    std::string operator()(int val) const;
    std::string operator()(float val) const;
    std::string operator()(std::string val) const;
};


class ToStringVis: public boost::static_visitor<std::string>
{
public:
    std::string operator()(int val) const;
    std::string operator()(float val) const;
    std::string operator()(std::string) const;
};



#endif //UXP1A_TUPLEVALVISITORS_H
