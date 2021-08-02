#ifndef IDATAMODELTABLECELLSIZES_H
#define IDATAMODELTABLECELLSIZES_H

class IDataModelTableCellSizes
{
public:
    virtual int minimumPreferedColumnWidth() const = 0;
    virtual int minimumPreferedRowHeight() const = 0;
};
#endif // ITABLEMINIMUMPREFEREDDIMENSIONS_H
