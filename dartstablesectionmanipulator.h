#ifndef DARTSTABLESECTIONMANIPULATOR_H
#define DARTSTABLESECTIONMANIPULATOR_H

#include "itablesectionmanipulator.h"
#include <qvector.h>
#include "linkedlist.h"
#include <qpair.h>

namespace TableDataContext {
    typedef QPair<int,int> PointInput;
    typedef LinkedList<PointInput> PointInputs;
    typedef  QVector<PointInputs> Rows;
}

class DartsTableSectionManipulator : public ITableSectionManipulator<TableDataContext::Rows>
{
public:
    typedef QPair<int,int> PointInput;
    typedef LinkedList<PointInput> PointInputs;
    typedef QVector<PointInputs> DataRows;
    virtual void removeRows(DataRows &data, const int &row, const int &count) const override
    {
        for (int i = row; i < row + count; ++i)
            data.removeAt(i);
    }
    virtual void removeColumns(DataRows &data, const int &column, const int &count) override
    {
        auto limit = column + count;
        for (int i = 0; i < data.count(); ++i) {
            auto row = data.at(i);
            for (int j = column; j < limit; ++j)
                row.removeAt(j);
            data.replace(i,row);
        }
    }
};


#endif // DARTSTABLEDATAMANIPULATOR_H
