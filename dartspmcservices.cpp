#include "dartspmcservices.h"

ITableContext *DartsPMCServices::tableContext() const
{
    return _tableContext;
}
void DartsPMCServices::setTableContext(ITableContext *newTableDimensions)
{
    _tableContext = newTableDimensions;
}
ITableCellContext<QPair<int, int> > *DartsPMCServices::cellContext() const
{
    return _cellContext;
}
void DartsPMCServices::setTableCellContext(ITableCellContext<QPair<int, int> > *newCellValueContext)
{
    _cellContext = newCellValueContext;
}
ITableFillCells<DartsPMCServices::Rows, DartsPMCServices::TableData> *DartsPMCServices::createRows() const
{
    return _createRows;
}
void DartsPMCServices::setCreateRows(ITableFillCells<Rows, TableData> *newFillCellsContext)
{
    _createRows = newFillCellsContext;
}
ITableIndiceValues *DartsPMCServices::createRowsIndices() const
{
    return _createRowIndiceValues;
}
void DartsPMCServices::setCreateRowsIndices(ITableIndiceValues *newCreateRowsIndices)
{
    _createRowIndiceValues = newCreateRowsIndices;
}
ITableDataManipulator<DartsPMCServices::Rows> *DartsPMCServices::tableDataManipulator() const
{
    return _tableDataManipulator;
}
void DartsPMCServices::setTableDataManipulator(ITableDataManipulator<Rows> *newTableDataManipulator)
{
    _tableDataManipulator = newTableDataManipulator;
}
ITableDataContext<DartsPMCServices::TableData, QModelIndex> *DartsPMCServices::dataContext() const
{
    return _dataContext;
}
void DartsPMCServices::setDataContext(ITableDataContext<TableData, QModelIndex> *newDataContext)
{
    _dataContext = newDataContext;
}
ITableIndiceValues *DartsPMCServices::createColumnIndiceValues() const
{
    return _createColumnIndiceValues;
}
void DartsPMCServices::setCreateColumnIndiceValues(ITableIndiceValues *newCreateColumnIndiceValues)
{
    _createColumnIndiceValues = newCreateColumnIndiceValues;
}

IQMLDataBuilder<DartsPMCServices::Column, QVariantList> *DartsPMCServices::QMLVariantsContext() const
{
    return _QMLDataContext;
}

void DartsPMCServices::setQMLVariantsContext(IQMLDataBuilder<Column, QVariantList> *newQMLDataContext)
{
    _QMLDataContext = newQMLDataContext;
}

IQMLDataBuilder<DartsPMCServices::TableData, QVariant> *DartsPMCServices::QMLJsonContext() const
{
    return _qmlJsonContext;
}

void DartsPMCServices::setQMLJsonContext(IQMLDataBuilder<TableData, QVariant> *newCreateJsonFromModel)
{
    _qmlJsonContext = newCreateJsonFromModel;
}

IGetDataFromDataContext<DartsPMCServices::TableData, DartsPMCServices::TableDataContext> *DartsPMCServices::getDataFromDataContext() const
{
    return _getDataFromDataContext;
}

void DartsPMCServices::setGetDataFromDataContext(IGetDataFromDataContext<TableData, TableDataContext> *newGetDataFromDataContext)
{
    _getDataFromDataContext = newGetDataFromDataContext;
}

ITableFillCells<DartsPMCServices::Rows, DartsPMCServices::TableData> *DartsPMCServices::createColumns() const
{
    return _createColumns;
}
void DartsPMCServices::setCreateColumns(ITableFillCells<Rows, TableData> *newCreateColumns)
{
    _createColumns = newCreateColumns;
}
