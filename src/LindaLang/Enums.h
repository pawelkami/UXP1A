//
// Created by tomasz on 5/27/16.
//

#ifndef UXP1A_ENUMS_H
#define UXP1A_ENUMS_H

#include <unordered_map>


enum class Condition: unsigned
{
    EQ = 0,
    GE = 1,
    LE = 2,
    GR = 3,
    LS = 4,
    ANY = 5,
};

const std::unordered_map<unsigned, std::string> conditionTypeNames = {
        { static_cast<unsigned>(Condition::EQ), "==" },
        { static_cast<unsigned>(Condition::GE), ">=" },
        { static_cast<unsigned>(Condition::LE), "<=" },
        { static_cast<unsigned>(Condition::GR), ">" },
        { static_cast<unsigned>(Condition::LS), "<" },
        { static_cast<unsigned>(Condition::ANY), "*" },
};

inline const std::string getconditionTypeName(const Condition& condType)
{
    return conditionTypeNames.at(static_cast<unsigned int>(condType));
};

#endif //UXP1A_ENUMS_H
