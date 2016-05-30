
#ifndef UXP1A_TUPLE_H
#define UXP1A_TUPLE_H


#include <vector>
#include "TupleValue.h"
#include "TuplePattern.h"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

/**
 * Klasa reprezentująca krotkę
 */

class Tuple
{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & values;
    }

    /**
     * Lista wartości będących w krotce
     */
    std::vector<TupleValue> values;

public:
    const std::vector<TupleValue> &getValues() const;

    void setValues(const std::vector<TupleValue> &values);


    void addValue(const TupleValue& value);

    /**
     * Metoda odpowiedzialna za sprawdzenie czy krotka pasuje do patternu.
     */
    bool checkPattern(const TuplePattern& pattern);

};


#endif //UXP1A_TUPLE_H
