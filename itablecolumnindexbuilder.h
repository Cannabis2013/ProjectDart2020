#ifndef ITABLECOLUMNINDEXBUILDER_H
#define ITABLECOLUMNINDEXBUILDER_H
#include "idartstabledatacontext.h"
#include "idartstablesectionutility.h"
class ITableColumnIndexBuilder
{
public:
    virtual int columnOf(const int &indexOf, const int &columnCount,
                         const IDartsTableDataContext *dataContext) const = 0;
};
#endif // ITABLECREATECOLUMN_H
