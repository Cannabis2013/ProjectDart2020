#ifndef DARTSTABLECREATEROWS_H
#define DARTSTABLECREATEROWS_H

#include "itablefillcells.h"
#include <qvector.h>
#include "linkedlist.h"
#include <qpair.h>

namespace FillRowNameSpace {
    typedef QPair<int,int> PointInput;
    typedef LinkedList<PointInput> PointInputs;
    typedef QVector<PointInputs> RowOfPointInputs;
}
class DartsTableCreateRows : public ITableFillCells<FillRowNameSpace::RowOfPointInputs,FillRowNameSpace::PointInput>
{
public:
    // Public types
    typedef QPair<int,int> PointInput;
    typedef LinkedList<PointInput> PointInputs;
    typedef QVector<PointInputs> RowOfPointInputs;
    virtual void fill(const int &row, const int &rows, const int &columns,
                      RowOfPointInputs &list,
                      const PointInput &defaultValue) const override
    {
        for (int i = 0; i < rows; ++i) {
            auto initializedDataRow = [=]
            {
                PointInputs resultingList;
                for (int i = 0; i < columns; ++i)
                    resultingList << defaultValue;
                return resultingList;
            }();
            list.insert(row,initializedDataRow);
        }
    }
};



#endif // DARTSTABLEFILLSERVICE_H
