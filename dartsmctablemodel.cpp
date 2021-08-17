#include "dartsmctablemodel.h"

DartsMCTableModel::DartsMCTableModel()
{
    connect(this,&DartsMCTableModel::initialValueChanged,
            this,&DartsMCTableModel::updateInitialCellValues);
}
bool DartsMCTableModel::insertData(const int &indexOfPlayer,const int &point,const int &score)
{
    auto modelIndex = createIndexFromPlayerName(indexOfPlayer);
    return setData(modelIndex,QVariant::fromValue<TableData>(TableData(point,score)),Qt::DisplayRole);;
}
bool DartsMCTableModel::removeLastItem(const int &indexOfPlayer)
{
    auto column = indexOfLastDecoratedCell(indexOfPlayer);
    auto index = createIndex(indexOfPlayer,column);
    auto result = removeData(index);
    return result;
}
void DartsMCTableModel::clearData()
{
    dataContext()->clear();
    auto bottomRight = createIndex(rowCount(QModelIndex()) - 1,columnCount() - 1);
    tableContext()->setColumns(minimumColumnCount());
    tableContext()->setRows(0);
    emit dataChanged(createIndex(0,0),bottomRight);
}
int DartsMCTableModel::columnCount() const
{
    return columnCount(QModelIndex());
}
int DartsMCTableModel::rowCount(const QModelIndex &) const
{
    return tableContext()->rows();
}
int DartsMCTableModel::columnCount(const QModelIndex &) const
{
    return tableContext()->columns();
}
QVariant DartsMCTableModel::data(const QModelIndex &index, int) const
{
    if(!index.isValid() || dataContext()->rowCount() <= 0) return QVariant();
    auto dataItem = dataContext()->item(index);
    return QMLJsonContext()->createData(dataItem);
}
bool DartsMCTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row() < 0 || index.column() < 0) return false;
    createRowsAndColumns(index);
    addValue(index,value);
    emit dataChanged(index,index,{role});
    return true;
}
bool DartsMCTableModel::insertRows(int row, int count, const QModelIndex &)
{
    auto indices = createRowsIndices()->createIndiceValues(row,rowCount(QModelIndex()),count);
    beginInsertRows(QModelIndex(),indices.first,indices.last);
    createRows()->fill(row,indices.count,columnCount(),dataContext()->rows(),cellContext()->defaultValues());
    endInsertRows();
    tableContext()->incrementRows(indices.count);
    emit dataChanged(createIndex(row,0),createIndex(indices.last,columnCount()));
    return true;
}
bool DartsMCTableModel::insertColumns(int column, int count, const QModelIndex &)
{
    auto indices = createColumnIndiceValues()->createIndiceValues(column,columnCount(),count);
    beginInsertColumns(QModelIndex(),indices.first,indices.last);
    createColumns()->fill(column,count,rowCount(QModelIndex()),dataContext()->rows(),cellContext()->defaultValues());
    endInsertColumns();
    tableContext()->incrementColumns(indices.count);
    emit dataChanged(createIndex(0,indices.first),createIndex(0,indices.last));
    return true;
}
bool DartsMCTableModel::removeRows(int row, int count, const QModelIndex &)
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
bool DartsMCTableModel::removeColumns(int column, int count, const QModelIndex &)
{
    if(column < 0 || column >= columnCount()) return false;
    beginRemoveColumns(QModelIndex(),column,column + count);
    tableDataManipulator()->removeColumns(dataContext()->rows(),column,count);
    tableContext()->decrementColumns(count);
    endRemoveColumns();
    emit dataChanged(QModelIndex(),QModelIndex());
    return true;
}
void DartsMCTableModel::updateInitialCellValues()
{
    for (int rowIndex = 0; rowIndex < rowCount(QModelIndex()); ++rowIndex)
        setData(createIndex(rowIndex,0),cellContext()->initialValue(),Qt::DisplayRole);
}
void DartsMCTableModel::createColumnsIfNecessary(const int &column)
{
    auto emptyColumn = dataContext()->isColumnEmpty(column,columnCount(),dataContext()->rows());
    auto indexOutOfRange = column > minimumColumnCount();
    if(emptyColumn && indexOutOfRange) removeColumns(column,1,QModelIndex());
}
void DartsMCTableModel::replaceValue(const QModelIndex &index, const TableData &model, Rows &data)
{
    auto rowData = data.at(index.row());
    auto initialPair = model;
    rowData.replace(index.column(),initialPair);
    dataContext()->replaceRow(index.row(),rowData);
}
QModelIndex DartsMCTableModel::createIndexFromPlayerName(const int &indexOfplayer) const
{
    auto rowCount = dataContext()->rowCount();
    auto column = indexOfplayer < rowCount ? indexOfLastDecoratedCell(indexOfplayer) + 1 : 0;
    return this->createIndex(indexOfplayer,column);
}
DartsMCTableModel::TableData DartsMCTableModel::addValue(const QModelIndex &index, const QVariant &value)
{
    auto rowData = dataContext()->rowAt(index.row());
    auto newPair = value.value<TableData>();
    rowData.replace(index.column(),newPair);
    dataContext()->replaceRow(index.row(),rowData);
    return newPair;
}
void DartsMCTableModel::createRowsAndColumns(const QModelIndex &index, const int &delta)
{
    if(index.row() >= rowCount(QModelIndex())) insertRows(index.row(),delta,QModelIndex());
    if(index.column() >= columnCount()) insertColumns(index.column(),delta,QModelIndex());
}
int DartsMCTableModel::indexOfLastDecoratedCell(const int &row) const
{
    return dataContext()->lastFilledCell(row,columnCount(),dataContext()->rows());
}
bool DartsMCTableModel::removeData(const QModelIndex &index)
{
    if(!index.isValid()) return false;
    replaceValue(index,cellContext()->defaultValues(),dataContext()->rows());
    createColumnsIfNecessary(index.column());
    emit dataChanged(createIndex(index.row(),index.column()),createIndex(index.row(),index.column()));
    return true;
}
void DartsMCTableModel::setInitialValue(int newInitialValue)
{
    cellContext()->setInitialValue(newInitialValue);
    emit initialValueChanged();
}
int DartsMCTableModel::initialValue() const
{
    return cellContext()->initialValue();
}
int DartsMCTableModel::minimumColumnCount() const
{
    return tableContext()->minimumColumnCount();
}
void DartsMCTableModel::setMinimumColumnCount(int minimumColumnCount)
{
    tableContext()->setMinimumColumnCount(minimumColumnCount);
    auto colCount = columnCount();
    if(minimumColumnCount > colCount) setColumnCount(minimumColumnCount);
    emit minimumColumnCountChanged();
}

QVariantList DartsMCTableModel::columnData(const int &column) const
{
    auto items = getDataFromDataContext()->itemsAtColumn(column,dataContext());
    return QMLVariantsContext()->createData(items);
}

QVariantList DartsMCTableModel::rowData(const int &row) const
{
    auto items = getDataFromDataContext()->itemsAtRow(row,dataContext());
    return QMLVariantsContext()->createData(items);
}

int DartsMCTableModel::lastDecoratedColumn(const int &indexOfPlayer) const
{
    return indexOfLastDecoratedCell(indexOfPlayer);
}
void DartsMCTableModel::setColumnCount(const int &count)
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
