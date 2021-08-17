#ifndef GETDATAFROMDATACONTEXT_H
#define GETDATAFROMDATACONTEXT_H

#include "igetdatafromdatacontext.h"
#include "itabledatacontext.h"
#include "linkedlist.h"
#include <QModelIndex>
namespace GetDataContext {
    typedef QPair<int,int> RowItem;
    typedef LinkedList<RowItem> Row;
    typedef QVector<Row> Rows;
}

class GetDataFromDataContext :
        public IGetDataFromDataContext<GetDataContext::RowItem,
                                       ITableDataContext<GetDataContext::RowItem,QModelIndex>>
{
    typedef QVector<Item> Items;
    typedef QPair<int,int> RowItem;
    typedef LinkedList<RowItem> Row;
    typedef QVector<Row> Rows;
public:
    virtual Items itemsAtColumn(const int &column, const DataContext *context) const override
    {
        return getDataFromColumn(column,context->data());
    }
    virtual Items itemsAtRow(const int &row, const DataContext *context) const override
    {
        return getDataFromRow(context->rowAt(row));
    }
private:
    Items getDataFromColumn(const int &column, const Rows &data) const
    {
        Items items;
        for (const auto &d : data)
            items << d.value(column);
        return items;
    }
    Items getDataFromRow(const Row &data) const
    {
        Items items;
        for (int i = 0; i < data.count(); ++i)
            items << data.value(i);
        return items;
    }
};

#endif // GETDATAFROMDATACONTEXT_H
