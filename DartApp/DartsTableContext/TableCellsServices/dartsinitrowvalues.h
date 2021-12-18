#ifndef DARTSINITCELLVAL_H
#define DARTSINITCELLVAL_H
#include <qvector.h>
#include "DartsTableContext/LinkedList/linkedlist.h"
#include <qpair.h>
#include "DartsTableContext/TableSectionsSLAs/itableinitrowvalues.h"
class DartsInitRowValues : public ITableInitRowValues<QVector<LinkedList<QPair<int,int>>>,QPair<int,int>>
{
public:
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
