#ifndef DARTSPOINTMULTICOLUMNSERVICES_H
#define DARTSPOINTMULTICOLUMNSERVICES_H

#include <itablecellstylistics.h>
#include <itableheadercontext.h>
#include <idatamodeltablecellsizes.h>
#include <idatamodeltabledimensions.h>
#include "itableheaderstylistics.h"
#include "ifontmetriccontext.h"
#include "inumerictableheadercontext.h"

class DartsPointMultiColumnServices
{
public:
    ITableCellStylistics<QString> *fontContext() const
    {
        return _fontContext;
    }
    void setFontContext(ITableCellStylistics<QString> *newFontStylistics)
    {
        _fontContext = newFontStylistics;
    }
    IDataModelTableCellSizes *tableCellContext() const
    {
        return _tableCellContext;
    }
    void setTableCellContext(IDataModelTableCellSizes *newTableColumnRowSizes)
    {
        _tableCellContext = newTableColumnRowSizes;
    }
    IDataModelTableDimensions *tableContext() const
    {
        return _tableContext;
    }
    void setTableContext(IDataModelTableDimensions *newTableDimensions)
    {
        _tableContext = newTableDimensions;
    }
    ITableHeaderContext<QString> *verticalHeaderContext() const
    {
        return _verticalHeaderContext;
    }
    void setVerticalHeaderContext(ITableHeaderContext<QString> *newHeaderContext)
    {
        _verticalHeaderContext = newHeaderContext;
    }

    ITableHeaderStylistics<QString> *headerStylistics() const
    {
        return _headerStylistics;
    }
    void setHeaderStylistics(ITableHeaderStylistics<QString> *newHeaderStylistics)
    {
        _headerStylistics = newHeaderStylistics;
    }

    IFontMetricContext<QString> *fontMetricContext() const
    {
        return _fontMetricContext;
    }
    void setFontMetricContext(IFontMetricContext<QString> *context)
    {
        _fontMetricContext = context;
    }

    INumericTableHeaderContext<QString> *horizontalHeaderContext() const
    {
        return _horizontalHeaderContext;
    }
    void setHorizontalHeaderContext(INumericTableHeaderContext<QString> *context)
    {
        _horizontalHeaderContext = context;
    }
private:
    // Header services
    ITableCellStylistics<QString> *_fontContext;
    ITableHeaderStylistics<QString> *_headerStylistics;
    ITableHeaderContext<QString> *_verticalHeaderContext;
    INumericTableHeaderContext<QString> *_horizontalHeaderContext;
    // Cell services
    IDataModelTableCellSizes *_tableCellContext;
    IDataModelTableDimensions *_tableContext;
    // Font utility services
    IFontMetricContext<QString> *_fontMetricContext;
};
#endif // DATAMODELSERVICES_H
