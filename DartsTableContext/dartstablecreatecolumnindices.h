#ifndef DARTSTABLECREATECOLUMNINDICES_H
#define DARTSTABLECREATECOLUMNINDICES_H

#include "itableindicevalues.h"
class DartsTableCreateColumnIndices : public ITableIndiceValues
{
public:
    virtual IndiceValues createIndiceValues(const int &start, const int &delta, const int &count) const override
    {
        IndiceValues values;
        values.first = start<= delta ? start : delta - 1;
        values.last =  start <= delta ? values.first + count : 2*start + count - values.first;
        values.count = start <= delta ? count : count + (start - values.first) - 1;
        return values;
    }
};



#endif // DARTSTABLECREATECOLUMNINDICES_H
