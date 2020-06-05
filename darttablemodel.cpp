#include "darttablemodel.h"

DartTableModel::DartTableModel()
{
}

bool DartTableModel::appendData(int row, int column, int data)
{
    auto dataIndex = this->createIndex(row,column);

    if(!dataIndex.isValid())
        return false;

    try {
        return setData(dataIndex,QVariant(data),Qt::DisplayRole);
    } catch (std::out_of_range *e) {
        printf("%s\n",e->what());
        return false;
    }
}

void DartTableModel::appendHeaderItem(const QVariant &data, const int &orientation)
{
    if(orientation == Qt::Horizontal)
        _horizontalHeaderData.append(data.toString());

    else
        _verticalHeaderData.append(data.toString());
}

QString DartTableModel::headerData(int index, int orientation) const
{
    auto value =  headerData(index,static_cast<Qt::Orientation>(orientation),Qt::DisplayRole).toString();

    return value;
}

int DartTableModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int DartTableModel::columnCount() const
{
    return columnCount(QModelIndex());
}

int DartTableModel::columnWithAt(const int &column, const QString &fontFamily, const int &pointSize) const
{
    auto font = QFont(fontFamily,pointSize);

    QFontMetrics fontMetric(font);

    auto string = _horizontalHeaderData.at(column);

    auto glyphLenght = fontMetric.boundingRect(string).width();

    return glyphLenght;
}

int DartTableModel::rowHeightAt(const int &row, const QString &fontFamily ,const int &pointSize) const
{
    auto font = QFont(fontFamily,pointSize);

    QFontMetrics fontMetric(font);

    auto string = _verticalHeaderData.at(row);

    auto glyphLenght = fontMetric.boundingRect(string).width();

    return glyphLenght;
}

int DartTableModel::rowCount(const QModelIndex &parent) const
{
    return _rows;
}

int DartTableModel::columnCount(const QModelIndex &parent) const
{
    return _columns;
}

QVariant DartTableModel::data(const QModelIndex &index, int role) const
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

QVariant DartTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    switch (orientation) {
        case Qt::Horizontal : return section < columnCount() ?
                    _horizontalHeaderData.count() > 0 ?
                        _horizontalHeaderData.at(section) : QVariant(section + 1) : QVariant();
        case Qt::Vertical : return section < _verticalHeaderData.count() ?
                    _verticalHeaderData.count() > 0  ?
                        _verticalHeaderData.at(section) : QVariant(section + 1): QVariant();
        default: return QVariant();
    }
}

bool DartTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto row = index.row();
    auto column = index.column();

    if(row < 0 || column < 0)
        return false;
    /*
    if(row >= _verticalHeaderData.count())
        throw new std::out_of_range("You need to allocate corresponding header rows before adding new data rows");
    */
    if(row >= rowCount())
        insertRows(row,1,QModelIndex());
    if(column >= columnCount())
        insertColumns(column,1,QModelIndex());

    auto r = _cellData.at(row);

    r.replace(column,value.toInt());

    _cellData.replace(row,r);

    emit dataChanged(index,index,{role});

    return true;
}

bool DartTableModel::insertRows(int row, int count, const QModelIndex &)
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

        _cellData.insert(row,rowData);
    }

    endInsertRows();

    _rows += c;

    return true;
}

bool DartTableModel::insertColumns(int column, int count, const QModelIndex &parent)
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

bool DartTableModel::removeRows(int row, int count, const QModelIndex &)
{
    // Check if input satisfies model constraints
    if(row < 0 || row >= rowCount())
        return false;

    // Create bounding indexes
    auto topLeftIndex = createIndex(row,0);
    auto bottomRightIndex = createIndex(row + count,columnCount() - 1);

    // Begin remove rows
    beginRemoveRows(QModelIndex(),row,row + count);

    for (int i = row; i < row + count; ++i)
    {
        _cellData.removeAt(i);
        // Remove corresponding header rows
        _verticalHeaderData.removeAt(i);
    }

    endRemoveRows();

    // Notify model and surrounding state that data has changed
    emit dataChanged(topLeftIndex,bottomRightIndex,{Qt::DisplayRole});

    return true;
}

bool DartTableModel::removeColumns(int column, int count, const QModelIndex &)
{
    // Check if input satisfies model constraints
    if(column < 0 || column >= columnCount())
        return false;

    // Create bounding indexes
    auto topLeftIndex = createIndex(0,column);
    auto bottomRightIndex = createIndex(rowCount() - 1,column + count);

    // Begin remove columns
    beginRemoveColumns(QModelIndex(),column,column + count);

    for (auto &row : _cellData) {
        for (int i = column; i < column + column; ++i)
            row.removeAt(i);
    }

    endRemoveColumns();

    // Notify model and surrounding state that data has changed
    emit dataChanged(topLeftIndex,bottomRightIndex,{Qt::DisplayRole});

    return true;
}

int DartTableModel::lastDecoratedCellIndex(int row)
{
    auto r = _cellData.at(row);

    for (int i = 0; i < columnCount(QModelIndex()); ++i) {
        auto cellValue = r.at(i);

        if(cellValue == -1)
            return i;
    }

    return columnCount(QModelIndex());
}
