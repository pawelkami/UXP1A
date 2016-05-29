#include "TupleSpace.h"

TupleSpace::TupleSpace()
{

}

void TupleSpace::insertTuple(Tuple& tuple)
{
    tuples.push_back(tuple);
}

Tuple TupleSpace::getTuple(TuplePattern& pattern)
{
    return *findTuple(pattern);
}

void TupleSpace::removeTuple(TuplePattern& tuple)
{
    tuples.erase(findTuple(tuple));
}

std::vector<Tuple>::const_iterator TupleSpace::findTuple(TuplePattern& pattern)
{
    for(auto &it : tuples)
    {

    }
    return nullptr;
}