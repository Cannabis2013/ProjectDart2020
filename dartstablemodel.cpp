#include "dartstablemodel.h"

DartsTableModel::DartsTableModel()
{
    connect(this,&DartsTableModel::initialValueChanged,
            this,&DartsTableModel::updateInitialCellValues);
}
bool DartsTableModel::insertData(const int &indexOfPlayer,const int &point,const int &score)
{
    auto column = columnIndexBuilder()->columnOf(indexOfPlayer,columnCount(),dataContext());
    auto modelIndex = createIndex(indexOfPlayer,column);
    return setData(modelIndex,QVariant::fromValue<TableItem>(TableItem(point,score)),Qt::DisplayRole);;
}
bool DartsTableModel::removeLastItem(const int &indexOfPlayer)
{
    auto column = columnIndexBuilder()->columnOf(indexOfPlayer,columnCount(),dataContext());
    auto modelIndex = createIndex(indexOfPlayer,column);
    auto result = removeData(modelIndex);
    return result;
}
void DartsTableModel::clearData()
{
    dataContext()->clear();
    auto bottomRight = createIndex(rowCount(QModelIndex()) - 1,columnCount() - 1);
    tableContext()->setColumns(minimumColumnCount());
    tableContext()->setRows(0);
    emit dataChanged(createIndex(0,0),bottomRight);
}
int DartsTableModel::columnCount() const
{
    return columnCount(QModelIndex());
}
int DartsTableModel::rowCount(const QModelIndex &) const
{
    return tableContext()->rows();
}
int DartsTableModel::columnCount(const QModelIndex &) const
{
    return tableContext()->columns();
}
QVariant DartsTableModel::data(const QModelIndex &index, int) const
{
    if(!index.isValid() || dataContext()->rowCount() <= 0)
        return QVariant();
    auto dataItem = dataContext()->item(index);
    return tableItemBuilder()->createItem(dataItem);
}
bool DartsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    createRowsAndColumns(index);
    addValue(index,value);
    emit dataChanged(index,index,{role});
    return true;
}
bool DartsTableModel::insertRows(int row, int count, const QModelIndex &)
{
    auto indices = createRowsIndices()->createIndiceValues(row,rowCount(QModelIndex()),count);
    beginInsertRows(QModelIndex(),indices.first,indices.last);
    createRows()->fill(row,indices.count,columnCount(),dataContext()->rows(),cellContext()->defaultValues());
    endInsertRows();
    tableContext()->incrementRows(indices.count);
    emit dataChanged(createIndex(row,0),createIndex(indices.last,columnCount()));
    return true;
}
bool DartsTableModel::insertColumns(int column, int count, const QModelIndex &)
{
    auto indices = createColumnIndiceValues()->createIndiceValues(column,columnCount(),count);
    beginInsertColumns(QModelIndex(),indices.first,indices.last);
    createColumns()->fill(column,count,rowCount(QModelIndex()),dataContext()->rows(),cellContext()->defaultValues());
    endInsertColumns();
    tableContext()->incrementColumns(indices.count);
    emit dataChanged(createIndex(0,indices.first),createIndex(0,indices.last));
    return true;
}
bool DartsTableModel::removeRows(int row, int count, const QModelIndex &)
{
    if(row < 0 || row >= rowCount(QModelIndex())) return false;
    auto topLeftIndex = createIndex(row,0);
    auto bottomRightIndex = createIndex(row + count,columnCount() - 1);
    beginRemoveRows(QModelIndex(),row,row + count);
    tableDataManipulator()->removeRows(dataContext()->rows(),row,count);
    endRemoveRows();
    tableContext()->decrementRows(count);
    emit dataChanged(topLeftIndex,bottomRightIndex,{Qt::DisplayRole});
    return true;
}
bool DartsTableModel::removeColumns(int column, int count, const QModelIndex &)
{
    if(column < 0 || column >= columnCount()) return false;
    beginRemoveColumns(QModelIndex(),column,column + count);
    tableDataManipulator()->removeColumns(dataContext()->rows(),column,count);
    tableContext()->decrementColumns(count);
    endRemoveColumns();
    emit dataChanged(QModelIndex(),QModelIndex());
    return true;
}
void DartsTableModel::updateInitialCellValues()
{
    for (int rowIndex = 0; rowIndex < rowCount(QModelIndex()); ++rowIndex)
        setData(createIndex(rowIndex,0),cellContext()->initialValue(),Qt::DisplayRole);
}
void DartsTableModel::createColumnsIfNecessary(const int &column)
{
    auto emptyColumn = sectionUtility()->isSectionEmpty(column,dataContext()->rows());
    auto indexOutOfRange = column > minimumColumnCount();
    if(emptyColumn && indexOutOfRange) removeColumns(column,1,QModelIndex());
}
void DartsTableModel::replaceValue(const QModelIndex &index, const TableItem &model, Rows &data)
{
    auto rowData = data.at(index.row());
    auto initialPair = model;
    rowData.replace(index.column(),initialPair);
    dataContext()->replaceRow(index.row(),rowData);
}

DartsTableModel::TableItem DartsTableModel::addValue(const QModelIndex &index, const QVariant &value)
{
    auto rowData = dataContext()->rowAt(index.row());
    auto newPair = value.value<TableItem>();
    rowData.replace(index.column(),newPair);
    dataContext()->replaceRow(index.row(),rowData);
    return newPair;
}
void DartsTableModel::createRowsAndColumns(const QModelIndex &index, const int &delta)
{
    if(index.row() >= rowCount(QModelIndex()))
        insertRows(index.row(),delta,QModelIndex());
    if(index.column() >= columnCount())
        insertColumns(index.column(),delta,QModelIndex());
}
bool DartsTableModel::removeData(const QModelIndex &index)
{
    if(!index.isValid()) return false;
    replaceValue(index,cellContext()->defaultValues(),dataContext()->rows());
    createColumnsIfNecessary(index.column());
    emit dataChanged(createIndex(index.row(),index.column()),createIndex(index.row(),index.column()));
    return true;
}
void DartsTableModel::setInitialValue(int newInitialValue)
{
    cellContext()->setInitialValue(newInitialValue);
    emit initialValueChanged();
}
int DartsTableModel::initialValue() const
{
    return cellContext()->initialValue();
}
int DartsTableModel::minimumColumnCount() const
{
    return tableContext()->minimumColumnCount();
}
void DartsTableModel::setMinimumColumnCount(int minimumColumnCount)
{
    tableContext()->setMinimumColumnCount(minimumColumnCount);
    auto colCount = columnCount();
    if(minimumColumnCount > colCount) setColumnCount(minimumColumnCount);
    emit minimumColumnCountChanged();
}

QVariantList DartsTableModel::columnData(const int &column) const
{
    auto items = getDataFromDataContext()->itemsAtColumn(column,dataContext());
    return QMLVariantsContext()->createItem(items);
}

QVariantList DartsTableModel::rowData(const int &row) const
{
    auto items = getDataFromDataContext()->itemsAtRow(row,dataContext());
    return QMLVariantsContext()->createItem(items);
}

int DartsTableModel::lastDecoratedColumn(const int &indexOfPlayer) const
{
    return columnIndexBuilder()->columnOf(indexOfPlayer,columnCount(),dataContext()) - 1;
}
void DartsTableModel::setColumnCount(const int &count)
{
    if(count < 0) return;
    else if(count > columnCount())
    {
        auto deltaC = count - columnCount();
        insertColumns(columnCount(),deltaC,QModelIndex());
    }
    else
    {
        auto deltaC = columnCount() - count ;
        removeColumns(count,deltaC,QModelIndex());
    }
}
