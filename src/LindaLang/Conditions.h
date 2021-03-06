
#ifndef UXP1A_CONDITIONS_H
#define UXP1A_CONDITIONS_H

#include <unordered_map>



enum class Condition: unsigned
{
    EQ = 0,
    GE = 1,
    LE = 2,
    GR = 3,
    LS = 4,
    ANY = 5,
    SIZE
};

const std::unordered_map<unsigned, std::string> conditionTypeNames = {
        { static_cast<unsigned>(Condition::EQ), "" },
        { static_cast<unsigned>(Condition::GE), ">=" },
        { static_cast<unsigned>(Condition::LE), "<=" },
        { static_cast<unsigned>(Condition::GR), ">" },
        { static_cast<unsigned>(Condition::LS), "<" },
        { static_cast<unsigned>(Condition::ANY), "*" }
};

inline const std::string getconditionTypeName(const Condition& condType)
{
    return conditionTypeNames.at(static_cast<unsigned int>(condType));
};


template<Condition cond>
class ConditionTraits
{
};

namespace eqCheck
{
    template<typename Type>
    bool checkEQ(const Type &val1, const Type &val2)
    {
        return val1 == val2;
    }
    template<>
    inline bool checkEQ<float>(const float &val1, const float &val2)
    {
        return false;
    }
};


template<>
class ConditionTraits<Condition::EQ>
{
public:
    template<class Type>
    static bool fulfilled(const Type &val1, const Type &val2)
    {
        return eqCheck::checkEQ<Type>(val1, val2);
    }
};


namespace geCheck
{
    template<typename Type>
    bool checkGE(const Type &val1, const Type &val2)
    {
        return val1 >= val2;
    }
    template<>
    inline bool checkGE<float>(const float &val1, const float &val2)
    {
        return val1 > val2;
    }
};


template<>
class ConditionTraits<Condition::GE>
{
public:
    template<class Type>
    static bool fulfilled(const Type &val1, const Type &val2)
    {
        return geCheck::checkGE<Type>(val1, val2);
    }
};


namespace leCheck
{
    template<typename Type>
    bool checkLE(const Type &val1, const Type &val2)
    {
        return val1 <= val2;
    }
    template<>
    inline bool checkLE<float>(const float &val1, const float &val2)
    {
        return val1 < val2;
    }
};


template<>
class ConditionTraits<Condition::LE>
{
public:
    template<class Type>
    static bool fulfilled(const Type &val1, const Type &val2)
    {
        return leCheck::checkLE<Type>(val1, val2);
    }
};


template<>
class ConditionTraits<Condition::GR>
{
public:
    template<class Type>
    static bool fulfilled(const Type &val1, const Type &val2)
    {
        return val1 > val2;
    }
};

template<>
class ConditionTraits<Condition::LS>
{
public:
    template<class Type>
    static bool fulfilled(const Type &val1, const Type &val2)
    {
        return val1 < val2;
    }
};

template<>
class ConditionTraits<Condition::ANY>
{
public:
    template<class Type>
    static bool fulfilled(const Type &val1, const Type &val2)
    {
        return true;
    }
};




#endif
