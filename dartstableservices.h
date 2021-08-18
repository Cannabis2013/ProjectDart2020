#ifndef DARTSTABLESERVICES_H
#define DARTSTABLESERVICES_H

#include <idatamodeltablecellsizes.h>
#include <itablecontext.h>
#include "itablecellcontext.h"
#include "itablefillcells.h"
#include "itableindicevalues.h"
#include "itabledatamanipulator.h"
#include "idartstabledatacontext.h"
#include "iqmldatabuilder.h"
#include "igetdatafromdatacontext.h"
#include "itablecolumnindexbuilder.h"
#include "idartstablesectionutility.h"
class DartsTableServices
{
public:
    typedef QPair<int,int> TableItem;
    typedef LinkedList<TableItem> Row;
    typedef QVector<Row> Rows;
    typedef QVector<TableItem> Column;
    ITableContext *tableContext() const;
    void setTableContext(ITableContext *newTableDimensions);
    ITableCellContext<QPair<int, int> > *cellContext() const;
    void setTableCellContext(ITableCellContext<QPair<int, int> > *newCellValueContext);
    ITableFillCells<Rows, TableItem> *createRows() const;
    void setCreateRows(ITableFillCells<Rows, TableItem> *newFillCellsContext);
    ITableFillCells<Rows, TableItem> *createColumns() const;
    void setCreateColumns(ITableFillCells<Rows, TableItem> *newCreateColumns);
    ITableIndiceValues *createRowsIndices() const;
    void setCreateRowsIndices(ITableIndiceValues *newCreateRowsIndices);
    ITableDataManipulator<Rows> *tableDataManipulator() const;
    void setTableDataManipulator(ITableDataManipulator<Rows> *newTableDataManipulator);
    IDartsTableDataContext *dataContext() const;
    void setDataContext(IDartsTableDataContext *newDataContext);
    ITableIndiceValues *createColumnIndiceValues() const;
    void setCreateColumnIndiceValues(ITableIndiceValues *newCreateColumnIndiceValues);
    IQMLDataBuilder<Column, QVariantList> *QMLVariantsContext() const;
    void setQMLVariantsContext(IQMLDataBuilder<Column, QVariantList> *newQMLDataContext);
    IQMLDataBuilder<TableItem, QVariant> *tableItemBuilder() const;
    void setTableItemBuilder(IQMLDataBuilder<TableItem, QVariant> *newCreateJsonFromModel);
    IGetDataFromDataContext<TableItem, IDartsTableDataContext> *getDataFromDataContext() const;
    void setGetDataFromDataContext(IGetDataFromDataContext<TableItem, IDartsTableDataContext> *newGetDataFromDataContext);
    ITableColumnIndexBuilder *columnIndexBuilder() const;
    void setcolumnIndexBuilder(ITableColumnIndexBuilder *newTableColumnIndexBuilder);
    IDartsTableSectionUtility *sectionUtility() const;
    void setSectionUtitity(IDartsTableSectionUtility *newSectionUtitity);

private:
    // Cell services
    ITableContext *_tableContext;
    ITableCellContext<TableItem> *_cellContext;
    ITableFillCells<Rows,TableItem> *_createRows;
    ITableFillCells<Rows,TableItem> *_createColumns;
    ITableIndiceValues *_createRowIndiceValues;
    ITableIndiceValues *_createColumnIndiceValues;
    ITableDataManipulator<Rows> *_tableDataManipulator;
    IDartsTableDataContext *_dataContext;
    IQMLDataBuilder<TableItem,QVariant> *_qmlJsonContext;
    IQMLDataBuilder<Column,QVariantList> *_QMLDataContext;
    IGetDataFromDataContext<TableItem,IDartsTableDataContext> *_getDataFromDataContext;
    ITableColumnIndexBuilder *_columnIndexBuilder;
    IDartsTableSectionUtility *_sectionUtitity;
};

#endif // DATAMODELSERVICES_H
