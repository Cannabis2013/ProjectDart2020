#ifndef DARTSTABLECREATECOLUMNS_H
#define DARTSTABLECREATECOLUMNS_H

#include "DartsTableContext/TableSectionsSLAs/itableinitrowvalues.h"
#include <qpair.h>
#include "DartsTableContext/LinkedList/linkedlist.h"
#include <qvector.h>

namespace FillColumnNameSpace {
    typedef QPair<int,int> RowItem;
    typedef LinkedList<RowItem> Row;
    typedef QVector<Row> Rows;
}

class DartsTableCreateColumns : public ITableInitRowValues<FillColumnNameSpace::Rows,FillColumnNameSpace::RowItem>
{
    // ITableFillCells interface
public:
    virtual void fill(const int &start, const int &delta, const int &count,
                      FillColumnNameSpace::Rows &cells, const FillColumnNameSpace::RowItem &defaultValue) const override
    {
        for (int i = 0;i<count;i++) {
            auto rowData = cells.at(i);
            auto columnsDataIndice = createColumnIndice(delta,defaultValue);
            rowData.insert(start,columnsDataIndice);
            cells.replace(i,rowData);
        }
    }
private:
    FillColumnNameSpace::Row createColumnIndice(const int &count, const FillColumnNameSpace::RowItem &defaultValue) const
    {
        FillColumnNameSpace::Row columnsIndice;
        for (int i = 0; i < count; ++i)
            columnsIndice << defaultValue;
        return columnsIndice;
    }
};
#endif // DARTSTABLEFILLCOLUMN_H
