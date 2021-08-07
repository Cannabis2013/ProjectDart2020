#ifndef ITABLECELLCONTEXT_H
#define ITABLECELLCONTEXT_H

#include "linkedlist.h"
#include <qvector.h>

template<typename T>
class ITableCellContext
{
public:
    typedef T RowItem;
    typedef LinkedList<RowItem> Row;
    typedef QVector<Row> Rows;
    virtual int initialValue() const = 0;
    virtual void setInitialValue(const int &value) = 0;
    virtual T defaultValues() const = 0;
    virtual int indexOfLastDecoration(const int &row, const int &columnCount, const Rows &data) const = 0;
    virtual bool isColumnEmpty(const int &column, const int &columnsCount, const Rows &data) const = 0;
};
#endif // ITABLECELLVALUES_H
