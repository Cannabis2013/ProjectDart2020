#ifndef ITABLESECTIONCONTEXT_H
#define ITABLESECTIONCONTEXT_H

class ITableSectionContext
{
public:
    virtual void reset() = 0;
    virtual int rows() const = 0;
    virtual void setRows(const int &rows) = 0;
    virtual void incrementRows(const int &inc) = 0;
    virtual void decrementRows(const int &dec) = 0;
    virtual int columns() const = 0;
    virtual void setColumns(const int &columns) = 0;
    virtual void incrementColumns(const int &inc) = 0;
    virtual void decrementColumns(const int &dec) = 0;
    virtual int minimumColumnCount() const = 0;
    virtual void setMinimumColumnCount(const int &minimum) = 0;
    virtual int minimumRowCount() const = 0;
    virtual void setMinimumRowCount(const int &minimum) = 0;
};
#endif // IDATAMODELTABLEDIMENSIONS_H
