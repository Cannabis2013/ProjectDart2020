#include "dartspointmulticolumnservices.h"

ITableContext *DartsPointMultiColumnServices::tableContext() const
{
    return _tableContext;
}
void DartsPointMultiColumnServices::setTableContext(ITableContext *newTableDimensions)
{
    _tableContext = newTableDimensions;
}
ITableCellContext<QPair<int, int> > *DartsPointMultiColumnServices::cellContext() const
{
    return _cellContext;
}
void DartsPointMultiColumnServices::setTableCellContext(ITableCellContext<QPair<int, int> > *newCellValueContext)
{
    _cellContext = newCellValueContext;
}
ITableFillCells<DartsPointMultiColumnServices::DataRows, DartsPointMultiColumnServices::PointInputModel> *DartsPointMultiColumnServices::createRows() const
{
    return _createRows;
}
void DartsPointMultiColumnServices::setCreateRows(ITableFillCells<DataRows, PointInputModel> *newFillCellsContext)
{
    _createRows = newFillCellsContext;
}
ITableIndiceValues *DartsPointMultiColumnServices::createRowsIndices() const
{
    return _createRowIndiceValues;
}
void DartsPointMultiColumnServices::setCreateRowsIndices(ITableIndiceValues *newCreateRowsIndices)
{
    _createRowIndiceValues = newCreateRowsIndices;
}
ITableDataManipulator<DartsPointMultiColumnServices::DataRows> *DartsPointMultiColumnServices::tableDataManipulator() const
{
    return _tableDataManipulator;
}
void DartsPointMultiColumnServices::setTableDataManipulator(ITableDataManipulator<DataRows> *newTableDataManipulator)
{
    _tableDataManipulator = newTableDataManipulator;
}
ITableDataContext<DartsPointMultiColumnServices::PointInputModel, QModelIndex> *DartsPointMultiColumnServices::dataContext() const
{
    return _dataContext;
}
void DartsPointMultiColumnServices::setDataContext(ITableDataContext<PointInputModel, QModelIndex> *newDataContext)
{
    _dataContext = newDataContext;
}
ITableIndiceValues *DartsPointMultiColumnServices::createColumnIndiceValues() const
{
    return _createColumnIndiceValues;
}
void DartsPointMultiColumnServices::setCreateColumnIndiceValues(ITableIndiceValues *newCreateColumnIndiceValues)
{
    _createColumnIndiceValues = newCreateColumnIndiceValues;
}

ITableCreateVariant<DartsPointMultiColumnServices::PointInputModel> *DartsPointMultiColumnServices::createJsonFromModel() const
{
    return _createJsonFromModel;
}

void DartsPointMultiColumnServices::setCreateJsonFromModel(ITableCreateVariant<PointInputModel> *newCreateJsonFromModel)
{
    _createJsonFromModel = newCreateJsonFromModel;
}

ITableFillCells<DartsPointMultiColumnServices::DataRows, DartsPointMultiColumnServices::PointInputModel> *DartsPointMultiColumnServices::createColumns() const
{
    return _createColumns;
}
void DartsPointMultiColumnServices::setCreateColumns(ITableFillCells<DataRows, PointInputModel> *newCreateColumns)
{
    _createColumns = newCreateColumns;
}
