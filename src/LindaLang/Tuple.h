
#ifndef UXP1A_TUPLE_H
#define UXP1A_TUPLE_H


#include <vector>
#include "TupleValue.h"
#include "TuplePattern.h"

/**
 * Klasa reprezentująca krotkę
 */
class Tuple
{
private:
    /**
     * Lista wartości będących w krotce
     */
    std::vector<PValue> values;

public:
    const std::vector<PValue> &getValues() const;

    void setValues(const std::vector<PValue> &values);

    /**
     * Metoda odpowiedzialna za sprawdzenie czy krotka pasuje do patternu.
     */
    bool checkPattern(const TuplePattern& pattern);



};


#endif //UXP1A_TUPLE_H
