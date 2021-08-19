#include "dartstableservices.h"

ITableSectionContext *DartsTableServices::tableSections() const
{
    return _tableContext;
}
void DartsTableServices::setTableSections(ITableSectionContext *newTableDimensions)
{
    _tableContext = newTableDimensions;
}
ITableCellContext<QPair<int, int> > *DartsTableServices::cellContext() const
{
    return _cellContext;
}
void DartsTableServices::setTableCellContext(ITableCellContext<QPair<int, int> > *newCellValueContext)
{
    _cellContext = newCellValueContext;
}
ITableFillCells<DartsTableServices::Rows, DartsTableServices::TableItem> *DartsTableServices::createRows() const
{
    return _createRows;
}
void DartsTableServices::setCreateRows(ITableFillCells<Rows, TableItem> *newFillCellsContext)
{
    _createRows = newFillCellsContext;
}
ITableIndiceValues *DartsTableServices::createRowsIndices() const
{
    return _createRowIndiceValues;
}
void DartsTableServices::setCreateRowsIndices(ITableIndiceValues *newCreateRowsIndices)
{
    _createRowIndiceValues = newCreateRowsIndices;
}
ITableSectionManipulator<DartsTableServices::Rows> *DartsTableServices::sectionManipulator() const
{
    return _tableDataManipulator;
}
void DartsTableServices::setSectionManipulator(ITableSectionManipulator<Rows> *newTableDataManipulator)
{
    _tableDataManipulator = newTableDataManipulator;
}
IDartsTableDataContext *DartsTableServices::dataContext() const
{
    return _dataContext;
}
void DartsTableServices::setDataContext(IDartsTableDataContext *newDataContext)
{
    _dataContext = newDataContext;
}
ITableIndiceValues *DartsTableServices::createColumnIndiceValues() const
{
    return _createColumnIndiceValues;
}
void DartsTableServices::setCreateColumnIndiceValues(ITableIndiceValues *newCreateColumnIndiceValues)
{
    _createColumnIndiceValues = newCreateColumnIndiceValues;
}

IQMLDataBuilder<DartsTableServices::Column, QVariantList> *DartsTableServices::QMLVariantsContext() const
{
    return _QMLDataContext;
}

void DartsTableServices::setQMLVariantsContext(IQMLDataBuilder<Column, QVariantList> *newQMLDataContext)
{
    _QMLDataContext = newQMLDataContext;
}

IQMLDataBuilder<DartsTableServices::TableItem, QVariant> *DartsTableServices::tableItemBuilder() const
{
    return _qmlJsonContext;
}

void DartsTableServices::setTableItemBuilder(IQMLDataBuilder<TableItem, QVariant> *newCreateJsonFromModel)
{
    _qmlJsonContext = newCreateJsonFromModel;
}

IGetDataFromDataContext<DartsTableServices::TableItem, IDartsTableDataContext> *DartsTableServices::getDataFromDataContext() const
{
    return _getDataFromDataContext;
}

void DartsTableServices::setGetDataFromDataContext(IGetDataFromDataContext<TableItem, IDartsTableDataContext> *newGetDataFromDataContext)
{
    _getDataFromDataContext = newGetDataFromDataContext;
}

ITableColumnIndexBuilder *DartsTableServices::columnIndexBuilder() const
{
    return _columnIndexBuilder;
}

void DartsTableServices::setcolumnIndexBuilder(ITableColumnIndexBuilder *newTableColumnIndexBuilder)
{
    _columnIndexBuilder = newTableColumnIndexBuilder;
}

IDartsTableSectionUtility *DartsTableServices::sectionUtility() const
{
    return _sectionUtitity;
}

void DartsTableServices::setSectionUtitity(IDartsTableSectionUtility *newSectionUtitity)
{
    _sectionUtitity = newSectionUtitity;
}

ITableFillCells<DartsTableServices::Rows, DartsTableServices::TableItem> *DartsTableServices::createColumns() const
{
    return _createColumns;
}
void DartsTableServices::setCreateColumns(ITableFillCells<Rows, TableItem> *newCreateColumns)
{
    _createColumns = newCreateColumns;
}
