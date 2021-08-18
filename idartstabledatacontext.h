#ifndef IDARTSTABLEDATACONTEXT_H
#define IDARTSTABLEDATACONTEXT_H

#include "linkedlist.h"
#include <QModelIndex>
#include <qvector.h>
class IDartsTableDataContext
{
public:
    typedef QModelIndex Index;
    typedef QPair<int,int> Item;
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
};


#endif // ITABLEDATACONTEXT_H
