#ifndef DARTSTABLESLAS_H
#define DARTSTABLESLAS_H
#include "DartsTableContext/TableSectionsSLAs/itablesectioncontext.h"
#include "DartsTableContext/TableSectionsSLAs/itablecellcontext.h"
#include "DartsTableContext/TableSectionsSLAs/itableinitrowvalues.h"
#include "itableindicevalues.h"
#include "DartsTableContext/TableSectionsSLAs/itablesectionmanipulator.h"
#include "DartsTableContext/DataContextSLAs/idartstabledatacontext.h"
#include "iqmldatabuilder.h"
#include "igetdatafromdatacontext.h"
#include "idartstablesectionutility.h"
class DartsTableSLAs : public QAbstractTableModel
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
    ITableInitRowValues<Rows, TableItem> *createRows() const;
    void setCreateRows(ITableInitRowValues<Rows, TableItem> *service);
    ITableInitRowValues<Rows, TableItem> *createColumns() const;
    void setCreateColumns(ITableInitRowValues<Rows, TableItem> *service);
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
    IGetDataFromDataContext<TableItem, IDartsTableDataContext> *getDataFromDataContext() const;
    void setGetDataFromDataContext(IGetDataFromDataContext<TableItem, IDartsTableDataContext> *service);
    IDartsTableSectionUtility *sectionUtility() const;
    void setSectionUtitity(IDartsTableSectionUtility *service);
private:
    ITableSectionContext *_tableContext;
    ITableCellContext<TableItem> *_cellContext;
    ITableInitRowValues<Rows,TableItem> *_createRows;
    ITableInitRowValues<Rows,TableItem> *_createColumns;
    ITableIndiceValues *_createRowIndiceValues;
    ITableIndiceValues *_createColumnIndiceValues;
    ITableSectionManipulator<Rows> *_tableDataManipulator;
    IDartsTableDataContext *_dataContext;
    IQMLDataBuilder<Column,QVariantList> *_QMLDataContext;
    IGetDataFromDataContext<TableItem,IDartsTableDataContext> *_getDataFromDataContext;
    IDartsTableSectionUtility *_sectionUtitity;
};

#endif // DATAMODELSERVICES_H
