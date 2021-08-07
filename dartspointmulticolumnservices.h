#ifndef DARTSPOINTMULTICOLUMNSERVICES_H
#define DARTSPOINTMULTICOLUMNSERVICES_H

#include <itablecellstylistics.h>
#include <itableheadercontext.h>
#include <idatamodeltablecellsizes.h>
#include <itablecontext.h>
#include <qvariant.h>
#include "itableheaderstylistics.h"
#include "ifontmetriccontext.h"
#include "inumerictableheadercontext.h"
#include "itablecellcontext.h"
#include "itablefillcells.h"
#include "linkedlist.h"
#include "itableindicevalues.h"
#include "itabledatamanipulator.h"
#include "itabledatacontext.h"
#include "itablecreatevariant.h"

class DartsPointMultiColumnServices
{
public:
    typedef QPair<int,int> PointInputModel;
    typedef LinkedList<PointInputModel> PointInputModels;
    typedef QVector<PointInputModels> DataRows;
    ITableContext *tableContext() const;
    void setTableContext(ITableContext *newTableDimensions);
    ITableCellContext<QPair<int, int> > *cellContext() const;
    void setTableCellContext(ITableCellContext<QPair<int, int> > *newCellValueContext);
    ITableFillCells<DataRows, PointInputModel> *createRows() const;
    void setCreateRows(ITableFillCells<DataRows, PointInputModel> *newFillCellsContext);
    ITableFillCells<DataRows, PointInputModel> *createColumns() const;
    void setCreateColumns(ITableFillCells<DataRows, PointInputModel> *newCreateColumns);
    ITableIndiceValues *createRowsIndices() const;
    void setCreateRowsIndices(ITableIndiceValues *newCreateRowsIndices);
    ITableDataManipulator<DataRows> *tableDataManipulator() const;
    void setTableDataManipulator(ITableDataManipulator<DataRows> *newTableDataManipulator);
    ITableDataContext<PointInputModel, QModelIndex> *dataContext() const;
    void setDataContext(ITableDataContext<PointInputModel, QModelIndex> *newDataContext);
    ITableIndiceValues *createColumnIndiceValues() const;
    void setCreateColumnIndiceValues(ITableIndiceValues *newCreateColumnIndiceValues);
    ITableCreateVariant<PointInputModel> *createJsonFromModel() const;
    void setCreateJsonFromModel(ITableCreateVariant<PointInputModel> *newCreateJsonFromModel);

private:
    // Cell services
    ITableContext *_tableContext;
    ITableCellContext<PointInputModel> *_cellContext;
    ITableFillCells<DataRows,PointInputModel> *_createRows;
    ITableFillCells<DataRows,PointInputModel> *_createColumns;
    ITableIndiceValues *_createRowIndiceValues;
    ITableIndiceValues *_createColumnIndiceValues;
    ITableDataManipulator<DataRows> *_tableDataManipulator;
    ITableDataContext<PointInputModel,QModelIndex> *_dataContext;
    ITableCreateVariant<PointInputModel> *_createJsonFromModel;
};
#endif // DATAMODELSERVICES_H
