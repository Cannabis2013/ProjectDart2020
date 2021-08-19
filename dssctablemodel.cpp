#include "dssctablemodel.h"

int DSSCTableModel::editData(const int &row, const int &column, const int &score)
{
    if(row < 0 || row >= rowCount())
        return -1;
    else if(column < 0 || column >= columnCount())
        return -1;
    auto index = createIndex(row,column);
    if(!isCellDecorated(index))
        return -1;
    auto oldData = this->data(index,Qt::DisplayRole);
    auto newData = score;
    if(!setData(index,newData,Qt::DisplayRole))
        return -1;
    return oldData.toInt();
}

bool DSSCTableModel::insertData(const QString &playerName,
                                         const int &score)
{
    return setPlayerData(playerName,score);;
}

bool DSSCTableModel::setPlayerData(const QString &playerName,
                                  const int &score)
{
    auto indexOfPlayer = indexOfHeaderItem(playerName);
    auto modelIndex = this->createIndex(indexOfPlayer,0);
    if(!modelIndex.isValid())
        return false;
    try {
        setData(modelIndex,score,Qt::DisplayRole);
    } catch (std::out_of_range *e) {
        printf("%s\n",e->what());
        return false;
    }
    return true;
}

bool DSSCTableModel::removeLastItem(const QString &playerName)
{
    auto column = indexOfHeaderItem(playerName);
    auto row = indexOfLastDecoratedField();
    auto index = createIndex(row,column);
    auto result = removeData(index);
    return result;
}

void DSSCTableModel::appendHeaderItem(const QVariant &data)
{
    auto glyphLength = stringWidth(data.toString(),
                                   scoreFontFamily(),
                                   headerFontSize());
    if(verticalHeaderCount() >= rowCount())
        insertRows(verticalHeaderCount(),1,QModelIndex());
    addVerticalHeaderData(data.toString());
    if(glyphLength > greatestVerticalHeaderWidth)
        greatestVerticalHeaderWidth = glyphLength;
    emit dataChanged(QModelIndex(),QModelIndex());
}

void DSSCTableModel::clearData()
{
    _data.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    _columns = 1;
    _rows = 0;
    _verticalHeaderData.clear();
    emit dataChanged(createIndex(0,0),bottomRight);
}

QString DSSCTableModel::getHeaderData(const int &index) const
{
    auto value = headerData(index,Qt::Vertical,Qt::DisplayRole).toString();
    return value;
}

int DSSCTableModel::headerItemCount() const
{
    auto count = _verticalHeaderData.count();
    return count;
}

int DSSCTableModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int DSSCTableModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double DSSCTableModel::columnWidthAt(const int &column)
{
    Q_UNUSED(column);
    return _columnWidth;
}

double DSSCTableModel::rowHeightAt(const int &row) const
{
    if(_data.count() <= 0)
        return 0;
    auto headerDataGlypHeight = rowHeightFromHeaderData(row);
    auto cellDataHeight = rowHeightFromCellDataAt(row);
    auto result = headerDataGlypHeight > cellDataHeight ? headerDataGlypHeight :
                                                          cellDataHeight;
    return result;
}

int DSSCTableModel::verticalHeaderCount() const
{
    return _verticalHeaderData.count();
}

int DSSCTableModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int DSSCTableModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

int DSSCTableModel::columnWidth() const
{
    return _columnWidth;
}

QVariant DSSCTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || _data.count() <= 0)
        return QVariant();
    if(role != Qt::DisplayRole)
        return QVariant();
    auto row = index.row();
    auto scoreValue = _data.at(row);
    auto data = QString::number(scoreValue);
    return scoreValue >= 0 ?
                QVariant(data) :
                QVariant("");
}

QVariant DSSCTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if(role != Qt::DisplayRole)
        return QVariant();
    return _verticalHeaderData.at(section);
}

bool DSSCTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Get row and column from index
    auto row = index.row();
    auto column = index.column();
    // Check for correctness
    if(row < 0 || column < 0)
        return false;
    if(row >= rowCount())
        insertRows(row,1,QModelIndex());
    // Set data
    auto data = value.toInt();
    _data.replace(row,data);
    // Update column width from column by the size of its data
    setColumnWidthByData(data);
    emit dataChanged(index,index,{role});
    return true;
}

bool DSSCTableModel::insertRows(int row, int count, const QModelIndex &)
{
    auto firstRow = row <= rowCount(QModelIndex()) ? row : rowCount(QModelIndex()) - 1;
    auto lastRow  =  row <= rowCount(QModelIndex()) ? firstRow + count : 2*row + count - firstRow;
    auto c = row <= rowCount(QModelIndex()) ? count : count + (row - firstRow) - 1;
    beginInsertRows(QModelIndex(),firstRow,lastRow);
    auto columnCount = this->columnCount();
    for (int i = 0; i < count; ++i)
        _data.append(-1);
    endInsertRows();
    _rows += c;
    emit dataChanged(createIndex(row,0),createIndex(lastRow,columnCount));
    return true;
}

bool DSSCTableModel::insertColumns(int column, int count, const QModelIndex &)
{
    auto firstColumn = column <= columnCount() ? column : columnCount() - 1;
    auto lastColumn  =  column <= columnCount() ? firstColumn + count : 2*column + count - firstColumn;
    auto c = column <= columnCount() ? count : count + (column - firstColumn) - 1;

    beginInsertColumns(QModelIndex(),firstColumn,lastColumn);
    initializeFieldsHorizontally(column);
    endInsertColumns();
    _columns += c;
    return true;
}

bool DSSCTableModel::removeRows(int row, int count, const QModelIndex &)
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
        _data.removeAt(i);
    endRemoveRows();

    _rows -= count;

    // Notify model and surrounding state that data has changed
    emit dataChanged(topLeftIndex,bottomRightIndex,{Qt::DisplayRole});

    return true;
}

bool DSSCTableModel::removeColumns(int column, int count, const QModelIndex &)
{
    // Check if input satisfies model constraints
    if(column < 0 || column >= columnCount())
        return false;
    // Begin remove columns
    auto limit = column + count;
    beginRemoveColumns(QModelIndex(),column,column + count);
    for (int i = 0; i < _data.count(); ++i) {
        for (int j = column; j < limit; ++j)
            _data.removeAt(j);
    }
    _columns -= count;
    endRemoveColumns();
    emit dataChanged(QModelIndex(),QModelIndex());

    return true;
}

void DSSCTableModel::updateInitialCellValues()
{

    if(_data.count() < 1)
        return;
    auto initialValue = this->initialValue();
    for (int i = 0; i < columnCount(); ++i)
        setData(createIndex(0,i),initialValue,Qt::DisplayRole);
}

void DSSCTableModel::setColumnWidthByData(const int& data)
{
    auto scoreGlypWidth = stringWidth(QString::number(data),
                                      scoreFontFamily(),
                                      scoreFontSize());
    if(scoreGlypWidth > _columnWidth)
        _columnWidth = scoreGlypWidth;
}

double DSSCTableModel::rowHeightFromHeaderData(const int &row) const
{

    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),headerFontSize()));
    auto headerData = _verticalHeaderData.at(row);
    auto headerDataGlyphHeight = scoreFontMetric.boundingRect(headerData).height();
    if(headerDataGlyphHeight < minimumPreferedRowHeight)
        return minimumPreferedRowHeight;
    return headerDataGlyphHeight;
}

double DSSCTableModel::rowHeightFromCellDataAt(const int &row) const
{
    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),scoreFontSize()));
    auto columnData = _data.at(row);
    auto scoreString = QString::number(columnData);
    auto scoreGlyphHeight = scoreFontMetric.boundingRect(scoreString).height();
    if(scoreGlyphHeight < minimumPreferedRowHeight)
        return minimumPreferedRowHeight;
    return scoreGlyphHeight;
}

void DSSCTableModel::initializeFieldsHorizontally(const int &startColumn,const int &initialValue)
{
    auto dataCount = _data.count();
    if(startColumn < dataCount)
        return;
    auto lastDecoratedField = indexOfLastDecoratedField();
    auto count = startColumn - lastDecoratedField;

    for (int i = 0; i < count; ++i)
        _data.append(initialValue);
}

bool DSSCTableModel::isIndexValid(const QModelIndex &index)
{
    auto row = index.row();
    auto column = index.column();
    if(row > 0)
        return false;
    else if(column >= _data.count())
        return false;
    return true;
}

bool DSSCTableModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int DSSCTableModel::indexOfLastDecoratedField()
{
    auto lastDecoratedField = _data.count() - 1;
    return lastDecoratedField;
}


bool DSSCTableModel::isRowEmpty(const int &row)
{
    if(row < 0 || row >= rowCount())
        throw std::out_of_range("Index out of range");
    for (int i = 0; i < _data.count(); ++i) {
        auto data = _data.at(i);
        if(data != -1)
            return false;
    }
    return true;
}

bool DSSCTableModel::removeData(const QModelIndex &index)
{
    if(!isIndexValid(index))
        return -1;
    auto row = index.row();
    auto column = index.column();
    if(isRowEmpty(row) && row > minimumRowCount())
    {
        removeColumns(column,1,QModelIndex());
        return true;
    }

    emit dataChanged(createIndex(row,column),createIndex(row,column));
    return false;
}

int DSSCTableModel::indexOfHeaderItem(const QString &data)
{
    auto index = _verticalHeaderData.indexOf(data);
    return index;
}

void DSSCTableModel::addVerticalHeaderData(const QString &data)
{
    _verticalHeaderData.append(data);
    emit dataChanged(QModelIndex(),QModelIndex());
}

int DSSCTableModel::stringWidth(const QString &string, const QString &family, const int &pointSize) const
{
    auto fontMetric = QFontMetrics(QFont(family,pointSize));
    auto r = fontMetric.boundingRect(string).width();
    return r;
}

int DSSCTableModel::headerFontSize() const
{
    return _headerFontSize;
}

void DSSCTableModel::setHeaderFontSize(int headerFontSize)
{
    _headerFontSize = headerFontSize;
}

QStringList DSSCTableModel::getVerticalHeaderData() const
{
    return _verticalHeaderData;
}

void DSSCTableModel::setVerticalHeaderData(const QList<QString> &horizontalHeaderData)
{
    _verticalHeaderData = horizontalHeaderData;
}

QString DSSCTableModel::pointFontFamily() const
{
    return _pointFontFamily;
}

void DSSCTableModel::setPointFontFamily(const QString &pointFontFamily)
{
    _pointFontFamily = pointFontFamily;
}

QString DSSCTableModel::scoreFontFamily() const
{
    return _scoreFontFamily;
}

void DSSCTableModel::setScoreFontFamily(const QString &scoreFontFamily)
{
    _scoreFontFamily = scoreFontFamily;
}

int DSSCTableModel::pointFontSize() const
{
    return _pointFontSize;
}

void DSSCTableModel::setPointFontSize(int pointFontSize)
{
    _pointFontSize = pointFontSize;
}

int DSSCTableModel::scoreFontSize() const
{
    return _scoreFontSize;
}

void DSSCTableModel::setScoreFontSize(int scoreFontSize)
{
    _scoreFontSize = scoreFontSize;
}

int DSSCTableModel::initialValue() const
{
    return _initialValue;
}

void DSSCTableModel::setInitialValue(int initialValue)
{
    _initialValue = initialValue;
    updateInitialCellValues();
}

int DSSCTableModel::minimumRowCount() const
{
    return _minimumRowCount;
}

void DSSCTableModel::setMinimumRowCount(int minimumRowCount)
{
    Q_UNUSED(minimumRowCount);
    return;
}

int DSSCTableModel::minimumColumnCount() const
{
    return _minimumColumnCount;
}

void DSSCTableModel::setMinimumColumnCount(int minimumColumnCount)
{
    Q_UNUSED(minimumColumnCount);
    return;
}

int DSSCTableModel::preferedHeaderItemWidth() const
{
    auto itemWidth = greatestVerticalHeaderWidth*_scale;
    return itemWidth;
}

void DSSCTableModel::setColumnCount(const int &count)
{
    if(count < 0)
        return;
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
    emit dataChanged(QModelIndex(),QModelIndex());
}

void DSSCTableModel::setRowCount(const int &count)
{
    if(count < 0)
        return;
    else if(count > rowCount())
    {
        auto deltaR = count - rowCount();
        insertRows(rowCount(),deltaR,QModelIndex());

    }
    else
    {
        auto deltaR = rowCount() - count ;
        removeRows(count,deltaR,QModelIndex());
    }
    emit minimumRowCountChanged();
}

double DSSCTableModel::scale() const
{
    return _scale;
}

void DSSCTableModel::setScale(double scale)
{
    _scale = scale;
}

int DSSCTableModel::horizontalHeaderFillMode() const
{
    return _horizontalFillMode;
}

void DSSCTableModel::setHorizontalHeaderFillMode(const int &fillMode)
{
    _horizontalFillMode = fillMode;
    emit fillModeChanged();
}

