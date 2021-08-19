#ifndef DARTSPSCINDEXBUILDER_H
#define DARTSPSCINDEXBUILDER_H

#include <itablecolumnindexbuilder.h>

class DartsPSCIndexBuilder : public ITableColumnIndexBuilder
{
public:
    virtual int columnOf(const int &indexOf, const int &columnCount, const IDartsTableDataContext *dataContext) const override
    {
        Q_UNUSED(indexOf);
        Q_UNUSED(columnCount);
        Q_UNUSED(dataContext);
        return 0;
    }
};
#endif // DARTSPSCCOLUMNINDEXBUILDER_H
