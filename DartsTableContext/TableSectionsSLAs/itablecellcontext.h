#ifndef ITABLECELLCONTEXT_H
#define ITABLECELLCONTEXT_H

#include "DartsTableContext/LinkedList/linkedlist.h"
#include <qvector.h>

template<typename T>
class ITableCellContext
{
public:
    typedef T Item;
    typedef LinkedList<Item> Row;
    typedef QVector<Row> Rows;
    typedef QVector<Item> Column;
    virtual int initialValue() const = 0;
    virtual void setInitialValue(const int &value) = 0;
    virtual T defaultValues() const = 0;
};
#endif // ITABLECELLVALUES_H
