#ifndef IDARTSTABLESECTIONUTILITY_H
#define IDARTSTABLESECTIONUTILITY_H

#include <QPair>
#include "linkedlist.h"
class IDartsTableSectionUtility
{
public:
    typedef QPair<int,int> RowItem;
    typedef LinkedList<RowItem> Row;
    typedef QVector<Row> Rows;
    virtual bool isSectionEmpty(const int &column, const Rows &data) const = 0;
};

#endif // IDARTSTABLESECTIONUTILITY_H
