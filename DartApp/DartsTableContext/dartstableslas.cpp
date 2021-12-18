#include "dartstableslas.h"

ITableSectionContext *DartsTableSLAs::tableSections() const
{
    return _tableContext;
}
void DartsTableSLAs::setTableSections(ITableSectionContext *service)
{
    _tableContext = service;
}
ITableCellContext<QPair<int, int> > *DartsTableSLAs::cellContext() const
{
    return _cellContext;
}
void DartsTableSLAs::setTableCellContext(ITableCellContext<QPair<int, int> > *service)
{
    _cellContext = service;
}
ITableInitRowValues<DartsTableSLAs::Rows, DartsTableSLAs::TableItem> *DartsTableSLAs::createRows() const
{
    return _createRows;
}
void DartsTableSLAs::setCreateRows(ITableInitRowValues<Rows, TableItem> *service)
{
    _createRows = service;
}
ITableIndiceValues *DartsTableSLAs::createRowsIndices() const
{
    return _createRowIndiceValues;
}
void DartsTableSLAs::setCreateRowsIndices(ITableIndiceValues *service)
{
    _createRowIndiceValues = service;
}
ITableSectionManipulator<DartsTableSLAs::Rows> *DartsTableSLAs::sectionManipulator() const
{
    return _tableDataManipulator;
}
void DartsTableSLAs::setSectionManipulator(ITableSectionManipulator<Rows> *service)
{
    _tableDataManipulator = service;
}
IDartsTableDataContext *DartsTableSLAs::dataContext() const
{
    return _dataContext;
}
void DartsTableSLAs::setDataContext(IDartsTableDataContext *service)
{
    _dataContext = service;
}
ITableIndiceValues *DartsTableSLAs::createColumnIndiceValues() const
{
    return _createColumnIndiceValues;
}
void DartsTableSLAs::setCreateColumnIndiceValues(ITableIndiceValues *service)
{
    _createColumnIndiceValues = service;
}
IQMLDataBuilder<DartsTableSLAs::Column, QVariantList> *DartsTableSLAs::QMLVariantsContext() const
{
    return _QMLDataContext;
}
void DartsTableSLAs::setQMLVariantsContext(IQMLDataBuilder<Column, QVariantList> *service)
{
    _QMLDataContext = service;
}
IGetDataFromDataContext<DartsTableSLAs::TableItem, IDartsTableDataContext> *DartsTableSLAs::getDataFromDataContext() const
{
    return _getDataFromDataContext;
}
void DartsTableSLAs::setGetDataFromDataContext(IGetDataFromDataContext<TableItem, IDartsTableDataContext> *service)
{
    _getDataFromDataContext = service;
}
IDartsTableSectionUtility *DartsTableSLAs::sectionUtility() const
{
    return _sectionUtitity;
}
void DartsTableSLAs::setSectionUtitity(IDartsTableSectionUtility *service)
{
    _sectionUtitity = service;
}
ITableInitRowValues<DartsTableSLAs::Rows, DartsTableSLAs::TableItem> *DartsTableSLAs::createColumns() const
{
    return _createColumns;
}
void DartsTableSLAs::setCreateColumns(ITableInitRowValues<Rows, TableItem> *service)
{
    _createColumns = service;
}
