#ifndef DARTSTABLEDATACONTEXT_H
#define DARTSTABLEDATACONTEXT_H

#include <qpair.h>
#include "itabledatacontext.h"

namespace TableDataContext {
    typedef QPair<int,int> DataRowItem;
    typedef LinkedList<DataRowItem> DataRow;
    typedef QVector<DataRow> DataRows;
}
#include <QModelIndex>
class DartsTableDataContext : public ITableDataContext<TableDataContext::DataRowItem,QModelIndex>
{
    typedef QPair<int,int> DataRowItem;
    typedef LinkedList<DataRowItem> DataRow;
    typedef QVector<DataRow> DataRows;
public:
    virtual Rows &rows() override
    {
        return _data;
    }
    virtual void replaceItem(const Index &index, const RowItem &model) override
    {
        auto dataRow = _data.at(index.row());
        dataRow.replace(index.column(),model);
        _data.replace(index.row(),dataRow);
    }
    virtual Row rowAt(const int &row) const override
    {
        return _data.at(row);
    }
    virtual RowItem item(const Index &index) const override
    {
        auto dataRow = _data.at(index.row());
        return dataRow.at(index.column());
    }
    virtual void clear() override
    {
        _data.clear();
    }
    virtual int rowCount() const override
    {
        return _data.count();
    }
    virtual void replaceRow(const int &row, const Row &data) override
    {
        _data.replace(row,data);
    }
private:
    DataRows _data;
};



#endif // DARTSTABLEDATACONTEXT_H
