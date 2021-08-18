#ifndef DARTSPMCCOLUMNINDEXBUILDER_H
#define DARTSPMCCOLUMNINDEXBUILDER_H

#include "itablecolumnindexbuilder.h"
#include <idartstabledatacontext.h>
#include <QModelIndex>
#include <QAbstractTableModel>

class DartsPMCColumnIndexBuilder : public ITableColumnIndexBuilder
{
public:
    virtual int columnOf(const int &indexOf, const int &columnCount,
                         const IDartsTableDataContext *dataContext) const override
    {
        return createColumnIndex(indexOf,columnCount,dataContext);
    }
private:
    int createColumnIndex(const int &indexOf,const int &columnCount, const IDartsTableDataContext *dataContext) const
    {
        if(isValid(indexOf,dataContext))
            return indexOfLastCell(indexOf,columnCount,dataContext->data());
        else
            return 0;
    }
    int indexOfLastCell(const int &indexOf, const int &columnCount, const IDartsTableDataContext::Rows &data) const
    {
        auto rowData = data.at(indexOf);
        for (int col = 0; col < columnCount; ++col) {
            auto columnData = rowData.at(col);
            auto point = columnData.first;
            if(point == -1)
                return col;
        }
        return columnCount;
    }
    bool isValid(const int &indexOf, const IDartsTableDataContext *context) const
    {
        return indexOf < context->rowCount();
    }
};
#endif // CREATECOLUMNFROMPLAYERINDEX_H
