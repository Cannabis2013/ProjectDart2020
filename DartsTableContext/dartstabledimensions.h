#ifndef DARTSTABLEDIMENSIONS_H
#define DARTSTABLEDIMENSIONS_H


#include "DartsTableContext/TableSectionsSLAs/itablesectioncontext.h"
class DartsTableDimensions : public ITableSectionContext
{
public:
    int rows() const override
    {
        return _rows;
    }
    int columns() const override
    {
        return _columns;
    }
    virtual void setRows(const int &rows) override
    {
        _rows = rows;
    }
    virtual void setColumns(const int &columns) override
    {
        _columns = columns;
    }
    virtual void setMinimumColumnCount(const int &minimum) override
    {
        _minimumColumnCount = minimum;
    }
    virtual void setMinimumRowCount(const int &minimum) override
    {
        _minimumRowCount = minimum;
    }
    int minimumColumnCount() const override
    {
        return _minimumColumnCount;
    }
    int minimumRowCount() const override
    {
        return _minimumRowCount;
    }
    virtual void incrementRows(const int &inc) override
    {
        _rows += inc;
    }
    virtual void incrementColumns(const int &inc) override
    {
        _columns += inc;
    }
    virtual void decrementRows(const int &dec) override
    {
        _rows -= dec;
    }
    virtual void decrementColumns(const int &dec) override
    {
        _columns -= dec;
    }
    virtual void reset() override
    {
        _rows = 0;
        _columns = _minimumColumnCount;
    }
private:
    int _rows = 0;
    int _columns = 0;
    int _minimumColumnCount = 0;
    int _minimumRowCount = 0;
};

#endif // DEFAULTDARTSTABLEDIMENSIONS_H
