#ifndef ITABLEDATACONTEXT_H
#define ITABLEDATACONTEXT_H

#include "linkedlist.h"
#include <qvector.h>
template<typename T, typename U>
class ITableDataContext
{
public:
    typedef U Index;
    typedef T Item;
    typedef LinkedList<Item> Row;
    typedef QVector<Row> Rows;
    virtual Rows data() const = 0;
    virtual Rows &rows() = 0;
    virtual int rowCount() const = 0;
    virtual Row rowAt(const int &row) const = 0;
    virtual Item item(const Index &index) const = 0;
    virtual void replaceItem(const Index &index, const Item &model) = 0;
    virtual void replaceRow(const int &row, const Row &data) = 0;
    virtual void clear() = 0;
    virtual int lastFilledCell(const int &row, const int &columnCount, const Rows &data) const = 0;
    virtual bool isColumnEmpty(const int &column, const int &columnsCount, const Rows &data) const = 0;
};


#endif // ITABLEDATACONTEXT_H
