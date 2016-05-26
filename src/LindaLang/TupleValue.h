
#ifndef UXP1A_TUPLEVALUE_H
#define UXP1A_TUPLEVALUE_H

#include <string>
#include <memory>

class TupleValue
{
public:
    virtual ~TupleValue() {};
};

/**
 * Klasa reprezentująca pojedynczą wartość będącą w krotce,
 */
template<class T>
class DetailedTupleValue : TupleValue
{
private:
    T value;

public:
    ~DetailedTupleValue() {};
    T getValue() const;

    void setValue(T val);

    std::string getTypeName() const;

    std::string toString() const;
};

typedef std::shared_ptr<TupleValue> PTupleValue;


#endif //UXP1A_TUPLEVALUE_H
