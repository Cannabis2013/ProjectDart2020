#include "dartspointmulticolumndatamodel.h"

DartsPointMultiColumnDataModel::DartsPointMultiColumnDataModel()
{
    connect(this,&DartsPointMultiColumnDataModel::initialValueChanged,this,&DartsPointMultiColumnDataModel::updateInitialCellValues);
}

bool DartsPointMultiColumnDataModel::insertData(const int &indexOfPlayer,const int &point,const int &score)
{
    auto modelIndex = createIndexFromPlayerName(indexOfPlayer);
    return setData(modelIndex,QVariant::fromValue<PointInputModel>(PointInputModel(point,score)),Qt::DisplayRole);;
}

bool DartsPointMultiColumnDataModel::removeLastItem(const int &indexOfPlayer)
{
    auto column = indexOfLastDecoratedCell(indexOfPlayer);
    auto index = createIndex(indexOfPlayer,column);
    auto result = removeData(index);
    return result;
}

void DartsPointMultiColumnDataModel::clearData()
{
    dataContext()->clear();
    auto bottomRight = createIndex(rowCount(QModelIndex()) - 1,columnCount() - 1);
    tableContext()->setColumns(minimumColumnCount());
    tableContext()->setRows(0);
    emit dataChanged(createIndex(0,0),bottomRight);
}


int DartsPointMultiColumnDataModel::columnCount() const
{
    return columnCount(QModelIndex());
}

int DartsPointMultiColumnDataModel::rowCount(const QModelIndex &) const
{
    return tableContext()->rows();
}

int DartsPointMultiColumnDataModel::columnCount(const QModelIndex &) const
{
    return tableContext()->columns();
}

QVariant DartsPointMultiColumnDataModel::data(const QModelIndex &index, int) const
{
    if(!index.isValid() || dataContext()->rowCount() <= 0) return QVariant();
    auto dataItem = dataContext()->item(index);
    return createJsonFromModel()->create(dataItem);
}

bool DartsPointMultiColumnDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Check if index is out of bounds
    if(index.row() < 0 || index.column() < 0) return false;
    // Create rows and columns if necessary
    createRowsAndColumns(index);
    // add value
    addValue(index,value);
    // Notify external context
    emit dataChanged(index,index,{role});
    return true;
}

bool DartsPointMultiColumnDataModel::insertRows(int row, int count, const QModelIndex &)
{
    // Create indices
    auto indices = createRowsIndices()->createIndiceValues(row,rowCount(QModelIndex()),count);
    // Create and fill with default values
    beginInsertRows(QModelIndex(),indices.first,indices.last);
    createRows()->fill(row,indices.count,columnCount(),dataContext()->rows(),cellContext()->defaultValues());
    endInsertRows();
    // Update tablecontext
    tableContext()->incrementRows(indices.count);
    // Notify external context
    emit dataChanged(createIndex(row,0),createIndex(indices.last,columnCount()));
    return true;
}

bool DartsPointMultiColumnDataModel::insertColumns(int column, int count, const QModelIndex &)
{
    auto indices = createColumnIndiceValues()->createIndiceValues(column,columnCount(),count);
    // Create and fill with default values
    beginInsertColumns(QModelIndex(),indices.first,indices.last);
    createColumns()->fill(column,count,rowCount(QModelIndex()),dataContext()->rows(),cellContext()->defaultValues());
    endInsertColumns();
    // Update tablecontext
    tableContext()->incrementColumns(indices.count);
    // Notify external context
    emit dataChanged(createIndex(0,indices.first),createIndex(0,indices.last));
    return true;
}

bool DartsPointMultiColumnDataModel::removeRows(int row, int count, const QModelIndex &)
{
    // Check if input satisfies model constraints
    if(row < 0 || row >= rowCount(QModelIndex())) return false;
    // Create bounding indexes
    auto topLeftIndex = createIndex(row,0);
    auto bottomRightIndex = createIndex(row + count,columnCount() - 1);
    // Remove rows
    beginRemoveRows(QModelIndex(),row,row + count);
    tableDataManipulator()->removeRows(dataContext()->rows(),row,count);
    endRemoveRows();
    tableContext()->decrementRows(count);
    // Notify model and surrounding state that data has changed
    emit dataChanged(topLeftIndex,bottomRightIndex,{Qt::DisplayRole});
    return true;
}

bool DartsPointMultiColumnDataModel::removeColumns(int column, int count, const QModelIndex &)
{
    // Check if input satisfies model constraints
    if(column < 0 || column >= columnCount()) return false;
    // Remove columns
    beginRemoveColumns(QModelIndex(),column,column + count);
    tableDataManipulator()->removeColumns(dataContext()->rows(),column,count);
    tableContext()->decrementColumns(count);
    endRemoveColumns();
    emit dataChanged(QModelIndex(),QModelIndex());
    return true;
}

void DartsPointMultiColumnDataModel::updateInitialCellValues()
{
    for (int rowIndex = 0; rowIndex < rowCount(QModelIndex()); ++rowIndex)
        setData(createIndex(rowIndex,0),cellContext()->initialValue(),Qt::DisplayRole);
}

void DartsPointMultiColumnDataModel::createColumnsIfNecessary(const int &column)
{
    auto emptyColumn = cellContext()->isColumnEmpty(column,columnCount(),dataContext()->rows());
    auto indexOutOfRange = column > minimumColumnCount();
    if(emptyColumn && indexOutOfRange)
        removeColumns(column,1,QModelIndex());
}

void DartsPointMultiColumnDataModel::replaceValue(const QModelIndex &index, const PointInputModel &model, DataRows &data)
{
    auto rowData = data.at(index.row());
    auto initialPair = model;
    rowData.replace(index.column(),initialPair);
    dataContext()->replaceRow(index.row(),rowData);
}

QModelIndex DartsPointMultiColumnDataModel::createIndexFromPlayerName(const int &indexOfplayer) const
{
    auto rowCount = dataContext()->rowCount();
    auto column = indexOfplayer < rowCount ? indexOfLastDecoratedCell(indexOfplayer) + 1 : 0;
    return this->createIndex(indexOfplayer,column);
}

DartsPointMultiColumnDataModel::PointInputModel DartsPointMultiColumnDataModel::addValue(const QModelIndex &index, const QVariant &value)
{
    auto rowData = dataContext()->rowAt(index.row());
    auto newPair = value.value<PointInputModel>();
    rowData.replace(index.column(),newPair);
    dataContext()->replaceRow(index.row(),rowData);
    return newPair;
}

void DartsPointMultiColumnDataModel::createRowsAndColumns(const QModelIndex &index, const int &delta)
{
    if(index.row() >= rowCount(QModelIndex()))
        insertRows(index.row(),delta,QModelIndex());
    if(index.column() >= columnCount())
        insertColumns(index.column(),delta,QModelIndex());
}

int DartsPointMultiColumnDataModel::indexOfLastDecoratedCell(const int &index) const
{
    return cellContext()->indexOfLastDecoration(index,columnCount(),dataContext()->rows());
}

bool DartsPointMultiColumnDataModel::removeData(const QModelIndex &index)
{
    if(!index.isValid()) return false;
    replaceValue(index,cellContext()->defaultValues(),dataContext()->rows());
    createColumnsIfNecessary(index.column());
    emit dataChanged(createIndex(index.row(),index.column()),createIndex(index.row(),index.column()));
    return true;
}

void DartsPointMultiColumnDataModel::setInitialValue(int newInitialValue)
{
    cellContext()->setInitialValue(newInitialValue);
    emit initialValueChanged();
}

int DartsPointMultiColumnDataModel::minimumColumnCount() const
{
    return tableContext()->minimumColumnCount();
}

void DartsPointMultiColumnDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    tableContext()->setMinimumColumnCount(minimumColumnCount);
    auto colCount = columnCount();
    if(minimumColumnCount > colCount) setColumnCount(minimumColumnCount);
    emit minimumColumnCountChanged();
}

void DartsPointMultiColumnDataModel::setColumnCount(const int &count)
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
