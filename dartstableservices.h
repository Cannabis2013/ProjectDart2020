#ifndef DARTSTABLESERVICES_H
#define DARTSTABLESERVICES_H

#include <idatamodeltablecellsizes.h>
#include <itablesectioncontext.h>
#include "itablecellcontext.h"
#include "itablefillcells.h"
#include "itableindicevalues.h"
#include "itablesectionmanipulator.h"
#include "idartstabledatacontext.h"
#include "iqmldatabuilder.h"
#include "igetdatafromdatacontext.h"
#include "itablecolumnindexbuilder.h"
#include "idartstablesectionutility.h"

class DartsTableServices : public QAbstractTableModel
{
public:
    typedef QPair<int,int> TableItem;
    typedef LinkedList<TableItem> Row;
    typedef QVector<Row> Rows;
    typedef QVector<TableItem> Column;
    ITableSectionContext *tableSections() const;
    void setTableSections(ITableSectionContext *service);
    ITableCellContext<QPair<int, int> > *cellContext() const;
    void setTableCellContext(ITableCellContext<QPair<int, int> > *service);
    ITableFillCells<Rows, TableItem> *createRows() const;
    void setCreateRows(ITableFillCells<Rows, TableItem> *service);
    ITableFillCells<Rows, TableItem> *createColumns() const;
    void setCreateColumns(ITableFillCells<Rows, TableItem> *service);
    ITableIndiceValues *createRowsIndices() const;
    void setCreateRowsIndices(ITableIndiceValues *service);
    ITableSectionManipulator<Rows> *sectionManipulator() const;
    void setSectionManipulator(ITableSectionManipulator<Rows> *service);
    IDartsTableDataContext *dataContext() const;
    void setDataContext(IDartsTableDataContext *service);
    ITableIndiceValues *createColumnIndiceValues() const;
    void setCreateColumnIndiceValues(ITableIndiceValues *service);
    IQMLDataBuilder<Column, QVariantList> *QMLVariantsContext() const;
    void setQMLVariantsContext(IQMLDataBuilder<Column, QVariantList> *service);
    IQMLDataBuilder<TableItem, QVariant> *tableItemBuilder() const;
    void setTableItemBuilder(IQMLDataBuilder<TableItem, QVariant> *service);
    IGetDataFromDataContext<TableItem, IDartsTableDataContext> *getDataFromDataContext() const;
    void setGetDataFromDataContext(IGetDataFromDataContext<TableItem, IDartsTableDataContext> *service);
    ITableColumnIndexBuilder *columnIndexBuilder() const;
    void setcolumnIndexBuilder(ITableColumnIndexBuilder *service);
    IDartsTableSectionUtility *sectionUtility() const;
    void setSectionUtitity(IDartsTableSectionUtility *service);

private:
    // Cell services
    ITableSectionContext *_tableContext;
    ITableCellContext<TableItem> *_cellContext;
    ITableFillCells<Rows,TableItem> *_createRows;
    ITableFillCells<Rows,TableItem> *_createColumns;
    ITableIndiceValues *_createRowIndiceValues;
    ITableIndiceValues *_createColumnIndiceValues;
    ITableSectionManipulator<Rows> *_tableDataManipulator;
    IDartsTableDataContext *_dataContext;
    IQMLDataBuilder<TableItem,QVariant> *_qmlJsonContext;
    IQMLDataBuilder<Column,QVariantList> *_QMLDataContext;
    IGetDataFromDataContext<TableItem,IDartsTableDataContext> *_getDataFromDataContext;
    ITableColumnIndexBuilder *_columnIndexBuilder;
    IDartsTableSectionUtility *_sectionUtitity;
};

#endif // DATAMODELSERVICES_H
