#include "dartstableservices.h"

ITableSectionContext *DartsTableServices::tableSections() const
{
    return _tableContext;
}
void DartsTableServices::setTableSections(ITableSectionContext *service)
{
    _tableContext = service;
}
ITableCellContext<QPair<int, int> > *DartsTableServices::cellContext() const
{
    return _cellContext;
}
void DartsTableServices::setTableCellContext(ITableCellContext<QPair<int, int> > *service)
{
    _cellContext = service;
}
ITableFillCells<DartsTableServices::Rows, DartsTableServices::TableItem> *DartsTableServices::createRows() const
{
    return _createRows;
}
void DartsTableServices::setCreateRows(ITableFillCells<Rows, TableItem> *service)
{
    _createRows = service;
}
ITableIndiceValues *DartsTableServices::createRowsIndices() const
{
    return _createRowIndiceValues;
}
void DartsTableServices::setCreateRowsIndices(ITableIndiceValues *service)
{
    _createRowIndiceValues = service;
}
ITableSectionManipulator<DartsTableServices::Rows> *DartsTableServices::sectionManipulator() const
{
    return _tableDataManipulator;
}
void DartsTableServices::setSectionManipulator(ITableSectionManipulator<Rows> *service)
{
    _tableDataManipulator = service;
}
IDartsTableDataContext *DartsTableServices::dataContext() const
{
    return _dataContext;
}
void DartsTableServices::setDataContext(IDartsTableDataContext *service)
{
    _dataContext = service;
}
ITableIndiceValues *DartsTableServices::createColumnIndiceValues() const
{
    return _createColumnIndiceValues;
}
void DartsTableServices::setCreateColumnIndiceValues(ITableIndiceValues *service)
{
    _createColumnIndiceValues = service;
}

IQMLDataBuilder<DartsTableServices::Column, QVariantList> *DartsTableServices::QMLVariantsContext() const
{
    return _QMLDataContext;
}

void DartsTableServices::setQMLVariantsContext(IQMLDataBuilder<Column, QVariantList> *service)
{
    _QMLDataContext = service;
}

IQMLDataBuilder<DartsTableServices::TableItem, QVariant> *DartsTableServices::tableItemBuilder() const
{
    return _qmlJsonContext;
}

void DartsTableServices::setTableItemBuilder(IQMLDataBuilder<TableItem, QVariant> *service)
{
    _qmlJsonContext = service;
}

IGetDataFromDataContext<DartsTableServices::TableItem, IDartsTableDataContext> *DartsTableServices::getDataFromDataContext() const
{
    return _getDataFromDataContext;
}

void DartsTableServices::setGetDataFromDataContext(IGetDataFromDataContext<TableItem, IDartsTableDataContext> *service)
{
    _getDataFromDataContext = service;
}

ITableColumnIndexBuilder *DartsTableServices::columnIndexBuilder() const
{
    return _columnIndexBuilder;
}

void DartsTableServices::setcolumnIndexBuilder(ITableColumnIndexBuilder *service)
{
    _columnIndexBuilder = service;
}

IDartsTableSectionUtility *DartsTableServices::sectionUtility() const
{
    return _sectionUtitity;
}

void DartsTableServices::setSectionUtitity(IDartsTableSectionUtility *service)
{
    _sectionUtitity = service;
}

ITableFillCells<DartsTableServices::Rows, DartsTableServices::TableItem> *DartsTableServices::createColumns() const
{
    return _createColumns;
}
void DartsTableServices::setCreateColumns(ITableFillCells<Rows, TableItem> *service)
{
    _createColumns = service;
}
