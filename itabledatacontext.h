#ifndef ITABLEDATACONTEXT_H
#define ITABLEDATACONTEXT_H

#include "linkedlist.h"
#include <qvector.h>
template<typename T, typename U>
class ITableDataContext
{
public:
    typedef U Index;
    typedef T RowItem;
    typedef LinkedList<RowItem> Row;
    typedef QVector<Row> Rows;
    virtual Rows &rows() = 0;
    virtual int rowCount() const = 0;
    virtual Row rowAt(const int &row) const = 0;
    virtual RowItem item(const Index &index) const = 0;
    virtual void replaceItem(const Index &index, const RowItem &model) = 0;
    virtual void replaceRow(const int &row, const Row &data) = 0;
    virtual void clear() = 0;
};
#endif // ITABLEDATACONTEXT_H
