#ifndef DARTSPMCSERVICES_H
#define DARTSPMCSERVICES_H

#include <idatamodeltablecellsizes.h>
#include <itablecontext.h>
#include "itablecellcontext.h"
#include "itablefillcells.h"
#include "itableindicevalues.h"
#include "itabledatamanipulator.h"
#include "itabledatacontext.h"
#include "iqmldatabuilder.h"
#include "igetdatafromdatacontext.h"

class DartsPMCServices
{
public:
    typedef QPair<int,int> TableData;
    typedef LinkedList<TableData> Row;
    typedef QVector<Row> Rows;
    typedef QVector<TableData> Column;
    typedef ITableDataContext<TableData,QModelIndex> TableDataContext;
    ITableContext *tableContext() const;
    void setTableContext(ITableContext *newTableDimensions);
    ITableCellContext<QPair<int, int> > *cellContext() const;
    void setTableCellContext(ITableCellContext<QPair<int, int> > *newCellValueContext);
    ITableFillCells<Rows, TableData> *createRows() const;
    void setCreateRows(ITableFillCells<Rows, TableData> *newFillCellsContext);
    ITableFillCells<Rows, TableData> *createColumns() const;
    void setCreateColumns(ITableFillCells<Rows, TableData> *newCreateColumns);
    ITableIndiceValues *createRowsIndices() const;
    void setCreateRowsIndices(ITableIndiceValues *newCreateRowsIndices);
    ITableDataManipulator<Rows> *tableDataManipulator() const;
    void setTableDataManipulator(ITableDataManipulator<Rows> *newTableDataManipulator);
    ITableDataContext<TableData, QModelIndex> *dataContext() const;
    void setDataContext(ITableDataContext<TableData, QModelIndex> *newDataContext);
    ITableIndiceValues *createColumnIndiceValues() const;
    void setCreateColumnIndiceValues(ITableIndiceValues *newCreateColumnIndiceValues);
    IQMLDataBuilder<Column, QVariantList> *QMLVariantsContext() const;
    void setQMLVariantsContext(IQMLDataBuilder<Column, QVariantList> *newQMLDataContext);
    IQMLDataBuilder<TableData, QVariant> *QMLJsonContext() const;
    void setQMLJsonContext(IQMLDataBuilder<TableData, QVariant> *newCreateJsonFromModel);
    IGetDataFromDataContext<TableData, TableDataContext> *getDataFromDataContext() const;
    void setGetDataFromDataContext(IGetDataFromDataContext<TableData, TableDataContext> *newGetDataFromDataContext);

private:
    // Cell services
    ITableContext *_tableContext;
    ITableCellContext<TableData> *_cellContext;
    ITableFillCells<Rows,TableData> *_createRows;
    ITableFillCells<Rows,TableData> *_createColumns;
    ITableIndiceValues *_createRowIndiceValues;
    ITableIndiceValues *_createColumnIndiceValues;
    ITableDataManipulator<Rows> *_tableDataManipulator;
    TableDataContext *_dataContext;
    IQMLDataBuilder<TableData,QVariant> *_qmlJsonContext;
    IQMLDataBuilder<Column,QVariantList> *_QMLDataContext;
    IGetDataFromDataContext<TableData,TableDataContext> *_getDataFromDataContext;
};
#endif // DATAMODELSERVICES_H
