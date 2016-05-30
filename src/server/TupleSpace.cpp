#include "TupleSpace.h"

TupleSpace::TupleSpace()
{

}

void TupleSpace::insertTuple(const Tuple& tuple)
{
    tuples.push_back(tuple);
}

bool TupleSpace::getTuple(const TuplePattern& pattern, Tuple& tuple)
{
    auto f = findTuple(pattern);
    if(f != tuples.end())
    {
        tuple.setValues(f->getValues());
        return true;
    }
    else
        return false;
}

bool TupleSpace::removeTuple(TuplePattern& tuple)
{
    auto f = findTuple(tuple);
    if(f != tuples.end())
    {
        tuples.erase(f);
        return true;
    }
    else
        return false;
}

std::vector<Tuple>::iterator TupleSpace::findTuple(const TuplePattern& pattern)
{
    for(std::vector<Tuple>::iterator it = tuples.begin(); it != tuples.end(); ++it)
    {
        if(it->checkPattern(pattern))
            return it;
    }
    return tuples.end();
}