#ifndef DARTSTABLECREATEROWS_H
#define DARTSTABLECREATEROWS_H

#include "itablefillcells.h"
#include <qvector.h>
#include "linkedlist.h"
#include <qpair.h>

class DartsTableCreateRows : public ITableFillCells<
        QVector<LinkedList<QPair<int,int>>>,QPair<int,int>>
{
public:
    // Public types
    typedef QPair<int,int> DataItem;
    typedef LinkedList<DataItem> Row;
    typedef QVector<Row> Rows;
    virtual void fill(const int &row, const int &rows, const int &columns,
                      Rows &list,const DataItem &defaultValue) const override
    {
        for (int i = 0; i < rows; ++i) {
            auto initializedDataRow = [=]
            {
                Row resultingList;
                for (int i = 0; i < columns; ++i)
                    resultingList << defaultValue;
                return resultingList;
            }();
            list.insert(row,initializedDataRow);
        }
    }
};
#endif // DARTSTABLEFILLSERVICE_H
