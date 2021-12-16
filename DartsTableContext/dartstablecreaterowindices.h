#ifndef DARTSTABLECREATEROWINDICES_H
#define DARTSTABLECREATEROWINDICES_H

#include "itableindicevalues.h"
class DartsTableCreateRowIndices : public ITableIndiceValues
{
public:
    virtual IndiceValues createIndiceValues(const int &row, const int &rows, const int &count) const override
    {
        auto firstRow = createFirstRow(row,rows);
        auto lastRow  =  createLastRow(row,rows,firstRow,count);
        auto c = createCount(row,rows,firstRow,count);
        return create(firstRow,lastRow,c);
    }
private:
    int createFirstRow(const int &row,const int &rows) const
    {
        return row <= rows ? row : rows - 1;
    }
    int createLastRow(const int &row, const int &rows, const int &first, const int &count) const
    {
        return row <= rows ? first + count : 2*row + count - first;
    }
    int createCount(const int &row, const int &rows, const int &first,const int &count) const
    {
        return row <= rows ? count : count + (row - first) - 1;
    }
    IndiceValues create(const int &first, const int &last, const int &count) const
    {
        IndiceValues indices;
        indices.first = first;
        indices.last = last;
        indices.count = count;
        return indices;
    }
};

#endif // DARTSTABLEROWINDICES_H
