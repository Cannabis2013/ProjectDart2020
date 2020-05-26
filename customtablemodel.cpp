#include "customtablemodel.h"

CustomTableModel::CustomTableModel()
{
}

void CustomTableModel::appendData(int row, int column, int data)
{
    auto dataIndex = this->createIndex(row,column);

    if(!dataIndex.isValid())
        return;

    setData(dataIndex,QVariant(data),Qt::DisplayRole);
}

int CustomTableModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int CustomTableModel::columnCount() const
{
    return columnCount(QModelIndex());
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    return _rows;
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    return _columns;
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= _cellData.count())
        return QVariant();

    auto rowData = _cellData.at(index.row());

    if(index.column() >= rowData.count())
        return QVariant();

    if(role != Qt::DisplayRole)
        return QVariant();

    auto data = rowData.at(index.column());

    return data >= 0 ?
                data :
                QVariant();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    switch (orientation) {
        case Qt::Horizontal : return section < _horizontalHeader.count() ? _horizontalHeader.at(section) : QVariant();
        case Qt::Vertical : return section < _verticalHeader.count() ?  _verticalHeader.at(section) : QVariant();
        default: return QVariant();
    }
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto row = index.row();
    auto column = index.column();

    if(row < 0 || column < 0)
        return false;

    if(row > rowCount(QModelIndex()) - 1)
        insertRows(row,1,QModelIndex());
    if(column > columnCount(QModelIndex()) - 1)
        insertColumns(column,1,QModelIndex());

    auto r = _cellData.at(row);

    r.replace(column,value.toInt());

    _cellData.replace(row,r);

    emit dataChanged(index,index,{role});

    return true;
}

bool CustomTableModel::insertRows(int row, int count, const QModelIndex &)
{
    auto firstRow = row <= rowCount(QModelIndex()) ? row : rowCount(QModelIndex()) - 1;
    auto lastRow  =  row <= rowCount(QModelIndex()) ? firstRow + count : 2*row + count - firstRow;
    auto c = row <= rowCount(QModelIndex()) ? count : count + (row - firstRow) - 1;

    beginInsertRows(QModelIndex(),firstRow,lastRow);

    for (int i = 0; i < c; ++i) {
        QList<int> rowData = [this]
        {
            QList<int> resultingList;
            for (int i = 0; i < columnCount(QModelIndex()); ++i)
                resultingList << -1;
            return resultingList;
        }();

        _verticalHeader.insert(row,"");

        _cellData.insert(row,rowData);
    }

    endInsertRows();

    _rows += c;

    return true;
}

bool CustomTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    auto firstColumn = column <= columnCount(QModelIndex()) ? column : columnCount(QModelIndex()) - 1;
    auto lastColumn  =  column <= columnCount(QModelIndex()) ? firstColumn + count : 2*column + count - firstColumn;
    auto c = column <= columnCount(QModelIndex()) ? count : count + (column - firstColumn) - 1;

    beginInsertColumns(QModelIndex(),firstColumn,lastColumn);

    for (QList<int> &row : _cellData) {
        QList<int> initialDataValues = [c]
        {
            QList<int> resultingList;

            for (int i = 0; i < c; ++i)
                resultingList << -1;

            return resultingList;
        }();
        for (int j = 0; j < initialDataValues.count(); ++j) {
            auto dataValue = initialDataValues.at(j);
            row.insert(column,dataValue);
        }
    }

    endInsertColumns();

    _columns += c;

    return true;
}

int CustomTableModel::lastDecoratedCellIndex(int row)
{
    auto r = _cellData.at(row);

    for (int i = 0; i < columnCount(QModelIndex()); ++i) {
        auto cellValue = r.at(i);

        if(cellValue == -1)
            return i;
    }

    return columnCount(QModelIndex());
}
