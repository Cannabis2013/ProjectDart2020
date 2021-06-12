#include "dartsscoresinglecolumndatamodel.h"

int DartsScoreSingleColumnDataModel::editData(const int &row, const int &column, const int &point, const int &score)
{
    if(row < 0 || row >= rowCount())
        return -1;
    else if(column < 0 || column >= columnCount())
        return -1;
    auto index = createIndex(row,column);
    if(!isCellDecorated(index))
        return -1;
    auto oldData = this->data(index,Qt::DisplayRole);
    auto newData = scoreModel(point,score);
    if(!setData(index,QVariant::fromValue<scoreModel>((newData)),Qt::DisplayRole))
        return -1;
    return oldData.toInt();
}

bool DartsScoreSingleColumnDataModel::insertData(const QString &playerName,
                                         const int &score)
{
    return setPlayerData(playerName,score);;
}

bool DartsScoreSingleColumnDataModel::setPlayerData(const QString &playerName,
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

bool DartsScoreSingleColumnDataModel::removeLastItem(const QString &playerName)
{
    auto column = indexOfHeaderItem(playerName);
    auto row = indexOfLastDecoratedField();
    auto index = createIndex(row,column);
    auto result = removeData(index);
    return result;
}

void DartsScoreSingleColumnDataModel::appendHeaderItem(const QVariant &data)
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

void DartsScoreSingleColumnDataModel::clearData()
{
    _data.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    _columns = 1;
    _rows = 0;
    _verticalHeaderData.clear();
    emit dataChanged(createIndex(0,0),bottomRight);
}

QString DartsScoreSingleColumnDataModel::getHeaderData(const int &index) const
{
    auto value = headerData(index,Qt::Vertical,Qt::DisplayRole).toString();
    return value;
}

int DartsScoreSingleColumnDataModel::headerItemCount() const
{
    auto count = _verticalHeaderData.count();
    return count;
}

int DartsScoreSingleColumnDataModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int DartsScoreSingleColumnDataModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double DartsScoreSingleColumnDataModel::columnWidthAt(const int &column)
{
    Q_UNUSED(column);
    return _columnWidth;
}

double DartsScoreSingleColumnDataModel::rowHeightAt(const int &row) const
{
    if(_data.count() <= 0)
        return 0;
    auto headerDataGlypHeight = rowHeightFromHeaderData(row);
    auto cellDataHeight = rowHeightFromCellDataAt(row);
    auto result = headerDataGlypHeight > cellDataHeight ? headerDataGlypHeight :
                                                          cellDataHeight;
    return result;
}

int DartsScoreSingleColumnDataModel::verticalHeaderCount() const
{
    return _verticalHeaderData.count();
}

int DartsScoreSingleColumnDataModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int DartsScoreSingleColumnDataModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

int DartsScoreSingleColumnDataModel::columnWidth() const
{
    return _columnWidth;
}

QVariant DartsScoreSingleColumnDataModel::data(const QModelIndex &index, int role) const
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

QVariant DartsScoreSingleColumnDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if(role != Qt::DisplayRole)
        return QVariant();
    return _verticalHeaderData.at(section);
}

int DartsScoreSingleColumnDataModel::numberOfAttemps() const
{
    return _attemps;
}

bool DartsScoreSingleColumnDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

bool DartsScoreSingleColumnDataModel::insertRows(int row, int count, const QModelIndex &)
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

bool DartsScoreSingleColumnDataModel::insertColumns(int column, int count, const QModelIndex &)
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

bool DartsScoreSingleColumnDataModel::removeRows(int row, int count, const QModelIndex &)
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

bool DartsScoreSingleColumnDataModel::removeColumns(int column, int count, const QModelIndex &)
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

void DartsScoreSingleColumnDataModel::updateInitialCellValues()
{

    if(_data.count() < 1)
        return;
    auto initialValue = this->initialValue();
    for (int i = 0; i < columnCount(); ++i)
        setData(createIndex(0,i),initialValue,Qt::DisplayRole);
}

void DartsScoreSingleColumnDataModel::setColumnWidthByData(const int& data)
{
    auto scoreGlypWidth = stringWidth(QString::number(data),
                                      scoreFontFamily(),
                                      scoreFontSize());
    if(scoreGlypWidth > _columnWidth)
        _columnWidth = scoreGlypWidth;
}

double DartsScoreSingleColumnDataModel::rowHeightFromHeaderData(const int &row) const
{

    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),headerFontSize()));
    auto headerData = _verticalHeaderData.at(row);
    auto headerDataGlyphHeight = scoreFontMetric.boundingRect(headerData).height();
    if(headerDataGlyphHeight < minimumPreferedRowHeight)
        return minimumPreferedRowHeight;
    return headerDataGlyphHeight;
}

double DartsScoreSingleColumnDataModel::rowHeightFromCellDataAt(const int &row) const
{
    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),scoreFontSize()));
    auto columnData = _data.at(row);
    auto scoreString = QString::number(columnData);
    auto scoreGlyphHeight = scoreFontMetric.boundingRect(scoreString).height();
    if(scoreGlyphHeight < minimumPreferedRowHeight)
        return minimumPreferedRowHeight;
    return scoreGlyphHeight;
}

void DartsScoreSingleColumnDataModel::initializeFieldsHorizontally(const int &startColumn,const int &initialValue)
{
    auto dataCount = _data.count();
    if(startColumn < dataCount)
        return;
    auto lastDecoratedField = indexOfLastDecoratedField();
    auto count = startColumn - lastDecoratedField;

    for (int i = 0; i < count; ++i)
        _data.append(initialValue);
}

bool DartsScoreSingleColumnDataModel::isIndexValid(const QModelIndex &index)
{
    auto row = index.row();
    auto column = index.column();
    if(row > 0)
        return false;
    else if(column >= _data.count())
        return false;
    return true;
}

bool DartsScoreSingleColumnDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int DartsScoreSingleColumnDataModel::indexOfLastDecoratedField()
{
    auto lastDecoratedField = _data.count() - 1;
    return lastDecoratedField;
}


bool DartsScoreSingleColumnDataModel::isRowEmpty(const int &row)
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

bool DartsScoreSingleColumnDataModel::removeData(const QModelIndex &index)
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

int DartsScoreSingleColumnDataModel::indexOfHeaderItem(const QString &data)
{
    auto index = _verticalHeaderData.indexOf(data);
    return index;
}

void DartsScoreSingleColumnDataModel::addVerticalHeaderData(const QString &data)
{
    _verticalHeaderData.append(data);
    emit dataChanged(QModelIndex(),QModelIndex());
}

int DartsScoreSingleColumnDataModel::stringWidth(const QString &string, const QString &family, const int &pointSize) const
{
    auto fontMetric = QFontMetrics(QFont(family,pointSize));
    auto r = fontMetric.boundingRect(string).width();
    return r;
}

int DartsScoreSingleColumnDataModel::headerFontSize() const
{
    return _headerFontSize;
}

void DartsScoreSingleColumnDataModel::setHeaderFontSize(int headerFontSize)
{
    _headerFontSize = headerFontSize;
}

QStringList DartsScoreSingleColumnDataModel::getVerticalHeaderData() const
{
    return _verticalHeaderData;
}

void DartsScoreSingleColumnDataModel::setVerticalHeaderData(const QList<QString> &horizontalHeaderData)
{
    _verticalHeaderData = horizontalHeaderData;
}

QString DartsScoreSingleColumnDataModel::pointFontFamily() const
{
    return _pointFontFamily;
}

void DartsScoreSingleColumnDataModel::setPointFontFamily(const QString &pointFontFamily)
{
    _pointFontFamily = pointFontFamily;
}

QString DartsScoreSingleColumnDataModel::scoreFontFamily() const
{
    return _scoreFontFamily;
}

void DartsScoreSingleColumnDataModel::setScoreFontFamily(const QString &scoreFontFamily)
{
    _scoreFontFamily = scoreFontFamily;
}

int DartsScoreSingleColumnDataModel::pointFontSize() const
{
    return _pointFontSize;
}

void DartsScoreSingleColumnDataModel::setPointFontSize(int pointFontSize)
{
    _pointFontSize = pointFontSize;
}

int DartsScoreSingleColumnDataModel::scoreFontSize() const
{
    return _scoreFontSize;
}

void DartsScoreSingleColumnDataModel::setScoreFontSize(int scoreFontSize)
{
    _scoreFontSize = scoreFontSize;
}

int DartsScoreSingleColumnDataModel::initialValue() const
{
    return _initialValue;
}

void DartsScoreSingleColumnDataModel::setInitialValue(int initialValue)
{
    _initialValue = initialValue;
    updateInitialCellValues();
}

int DartsScoreSingleColumnDataModel::minimumRowCount() const
{
    return _minimumRowCount;
}

void DartsScoreSingleColumnDataModel::setMinimumRowCount(int minimumRowCount)
{
    Q_UNUSED(minimumRowCount);
    return;
}

int DartsScoreSingleColumnDataModel::minimumColumnCount() const
{
    return _minimumColumnCount;
}

void DartsScoreSingleColumnDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    Q_UNUSED(minimumColumnCount);
    return;
}

int DartsScoreSingleColumnDataModel::preferedHeaderItemWidth() const
{
    auto itemWidth = greatestVerticalHeaderWidth*_scale;
    return itemWidth;
}

void DartsScoreSingleColumnDataModel::setNumberOfAttemps(const int &count)
{
    _attemps = count;
    emit dataChanged(QModelIndex(),QModelIndex());
}

void DartsScoreSingleColumnDataModel::setColumnCount(const int &count)
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

void DartsScoreSingleColumnDataModel::setRowCount(const int &count)
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

double DartsScoreSingleColumnDataModel::scale() const
{
    return _scale;
}

void DartsScoreSingleColumnDataModel::setScale(double scale)
{
    _scale = scale;
}

int DartsScoreSingleColumnDataModel::horizontalHeaderFillMode() const
{
    return _horizontalFillMode;
}

void DartsScoreSingleColumnDataModel::setHorizontalHeaderFillMode(const int &fillMode)
{
    _horizontalFillMode = fillMode;
    emit fillModeChanged();
}

