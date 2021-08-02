#ifndef DEFAULTDARTSCELLCONTEXT_H
#define DEFAULTDARTSCELLCONTEXT_H

#include "idatamodeltablecellsizes.h"
class DefaultDartsCellContext : public IDataModelTableCellSizes
{
public:
    int minimumPreferedColumnWidth() const override
    {
        return _minimumPreferedColumnWidth;
    }
    int minimumPreferedRowHeight() const override
    {
        return _minimumPreferedRowHeight;
    }
private:
    const int _minimumPreferedColumnWidth = 64;
    const int _minimumPreferedRowHeight = 25;
};

#endif // DEFAULTTABLEDIMENSIONS_H
