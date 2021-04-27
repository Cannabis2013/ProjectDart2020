#include "sftpdatamodel.h"

SFtpDataModel::SFtpDataModel()
{

}
int SFtpDataModel::editData(const int &row, const int &column, const int &point, const int &score)
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

bool SFtpDataModel::insertData(const QString &playerName,
                                         const int &point,
                                         const int &score)
{
    Q_UNUSED(point);
    return setPlayerData(playerName,score);;
}

bool SFtpDataModel::setPlayerData(const QString &playerName,
                                  const int &score)
{
    auto indexOfPlayer = indexOfHeaderItem(playerName);
    auto modelIndex = this->createIndex(0,indexOfPlayer);
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

bool SFtpDataModel::removeLastItem(const QString &playerName)
{
    auto column = indexOfHeaderItem(playerName);
    auto row = indexOfLastDecoratedField();
    auto index = createIndex(row,column);
    auto result = removeData(index);
    return result;
}

void SFtpDataModel::appendHeaderItem(const QVariant &data)
{
    auto glyphLength = stringWidth(data.toString(),
                                   scoreFontFamily(),
                                   headerFontSize());
    if(horizontalHeaderCount() >= columnCount())
        insertColumns(horizontalHeaderCount(),1,QModelIndex());
    addHorizontalHeaderData(data.toString());
    auto column = horizontalHeaderCount() - 1;
    if(glyphLength > columnWidthsAt(column))
        setColumnWidthAt(column,glyphLength);
    emit dataChanged(QModelIndex(),QModelIndex());
}

void SFtpDataModel::clearData()
{
    _data.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    _columns = 0;
    _rows = 0;

    _horizontalHeaderData.clear();

    emit dataChanged(createIndex(0,0),bottomRight);
}

QString SFtpDataModel::getHeaderData(const int &index) const
{
    auto value = headerData(index,Qt::Horizontal,Qt::DisplayRole).toString();
    return value;
}

int SFtpDataModel::headerItemCount() const
{
    if(horizontalHeaderFillMode() == HeaderFillMode::FixedStrings)
        return horizontalHeaderCount();
    else
        return columnCount();
}

int SFtpDataModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int SFtpDataModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double SFtpDataModel::columnWidthAt(const int &column) const
{
    auto s = scale();
    auto w = columnWidthsAt(column);
    auto columnWidth = s*w;
    if(columnWidth < minimumPreferedColumnWidth)
        return minimumPreferedColumnWidth;
    else
        return columnWidth;
}

double SFtpDataModel::rowHeightAt(const int &row) const
{
    if(_data.count() <= 0)
        return 0;

    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),scoreFontSize()));

    auto resultingGlyphLenght = 0;
    auto count = columnCount();
    for (int c = 0; c < count; ++c) {
        auto columnData = _data.at(row);
        auto scoreString = QString::number(columnData);
        auto scoreGlyphHeight = scoreFontMetric.boundingRect(scoreString).height();
        resultingGlyphLenght = scoreGlyphHeight > resultingGlyphLenght ?
                    scoreGlyphHeight: resultingGlyphLenght;
    }

    if(resultingGlyphLenght < minimumPreferedRowHeight)
        resultingGlyphLenght = minimumPreferedRowHeight;

    return resultingGlyphLenght;
}

int SFtpDataModel::horizontalHeaderCount() const
{
    return _horizontalHeaderData.count();
}

int SFtpDataModel::verticalHeaderCount() const
{
    return 0;
}

int SFtpDataModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int SFtpDataModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

void SFtpDataModel::setColumnWidthAt(const int &column, const double &w)
{
    _columnWidths.replace(column,w);
}

int SFtpDataModel::columnWidthsAt(const int &index) const
{
    auto columnWidth = _columnWidths.at(index);
    return columnWidth;
}

QVariant SFtpDataModel::data(const QModelIndex &index, int role) const
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

QVariant SFtpDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if(role != Qt::DisplayRole)
        return QVariant();

    auto roundIndex = (section - 1)/_attemps + 1;

    if(horizontalHeaderFillMode() == HeaderFillMode::DynamicNumerics)
        return QVariant(roundIndex);
    else if(horizontalHeaderFillMode() == HeaderFillMode::FixedStrings &&
            section < horizontalHeaderCount())
    {
        return _horizontalHeaderData.at(section);
    }
    else
        return QVariant();
}

int SFtpDataModel::numberOfAttemps() const
{
    return _attemps;
}

bool SFtpDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Get row and column from index
    auto row = index.row();
    auto column = index.column();
    // Check for correctness
    if(row < 0 || column < 0)
        return false;
    // Check if columns has to be made
    if(column >= columnCount())
        insertColumns(column,1,QModelIndex());
    // Likewise for rows
    if(row >= rowCount())
        insertRows(row,1,QModelIndex());
    // Set data
    auto data = value.toInt();
    _data.replace(column,data);
    // Update column width from column by the size of its data
    updateColumnWidth(column,data);
    emit dataChanged(index,index,{role});
    return true;
}

bool SFtpDataModel::insertRows(int row, int count, const QModelIndex &)
{
    auto firstRow = row <= rowCount(QModelIndex()) ? row : rowCount(QModelIndex()) - 1;
    auto lastRow  =  row <= rowCount(QModelIndex()) ? firstRow + count : 2*row + count - firstRow;
    auto c = row <= rowCount(QModelIndex()) ? count : count + (row - firstRow) - 1;
    beginInsertRows(QModelIndex(),firstRow,lastRow);
    auto columnCount = this->columnCount();
    for (int i = 0; i < columnCount; ++i)
        _data.insert(i,-1);
    endInsertRows();
    _rows += c;
    emit dataChanged(createIndex(row,0),createIndex(lastRow,columnCount));
    return true;
}

bool SFtpDataModel::insertColumns(int column, int count, const QModelIndex &)
{
    auto firstColumn = column <= columnCount() ? column : columnCount() - 1;
    auto lastColumn  =  column <= columnCount() ? firstColumn + count : 2*column + count - firstColumn;
    auto c = column <= columnCount() ? count : count + (column - firstColumn) - 1;

    beginInsertColumns(QModelIndex(),firstColumn,lastColumn);
    initializeFieldsHorizontally(column);
    setInitialColumnWidths(count);
    endInsertColumns();
    _columns += c;
    return true;
}

bool SFtpDataModel::removeRows(int row, int count, const QModelIndex &)
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

bool SFtpDataModel::removeColumns(int column, int count, const QModelIndex &)
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

void SFtpDataModel::updateInitialCellValues()
{

    if(_data.count() < 1)
        return;
    auto initialValue = this->initialValue();
    for (int i = 0; i < columnCount(); ++i)
        setData(createIndex(0,i),initialValue,Qt::DisplayRole);
}

void SFtpDataModel::updateColumnWidth(const int& column,const int& data)
{
    auto scoreGlypWidth = stringWidth(QString::number(data),
                                      scoreFontFamily(),
                                      scoreFontSize());
    if(scoreGlypWidth > columnWidthsAt(column))
        setColumnWidthAt(column,scoreGlypWidth);
}

void SFtpDataModel::setInitialColumnWidths(const int &count)
{
    QList<double> newColumnWidths;
    for (int i = 0; i < count; ++i)
        newColumnWidths << minimumPreferedColumnWidth;
    _columnWidths << newColumnWidths;
}

void SFtpDataModel::initializeFieldsHorizontally(const int &startColumn,const int &initialValue)
{
    auto dataCount = _data.count();
    if(startColumn < dataCount)
        return;
    auto lastDecoratedField = indexOfLastDecoratedField();
    auto count = startColumn - lastDecoratedField;

    for (int i = 0; i < count; ++i)
        _data.append(initialValue);
}

bool SFtpDataModel::isIndexValid(const QModelIndex &index)
{
    auto row = index.row();
    auto column = index.column();
    if(row > 0)
        return false;
    else if(column >= _data.count())
        return false;
    return true;
}

bool SFtpDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int SFtpDataModel::indexOfLastDecoratedField()
{
    auto lastDecoratedField = _data.count() - 1;
    return lastDecoratedField;
}


bool SFtpDataModel::isRowEmpty(const int &row)
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

bool SFtpDataModel::removeData(const QModelIndex &index)
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

int SFtpDataModel::indexOfHeaderItem(const QString &data)
{
    auto index = _horizontalHeaderData.indexOf(data);
    return index;
}

void SFtpDataModel::addHorizontalHeaderData(const QString &data)
{
    _horizontalHeaderData.append(data);
    emit dataChanged(QModelIndex(),QModelIndex());
}

int SFtpDataModel::stringWidth(const QString &string, const QString &family, const int &pointSize) const
{
    auto fontMetric = QFontMetrics(QFont(family,pointSize));
    auto r = fontMetric.boundingRect(string).width();
    return r;
}

int SFtpDataModel::headerFontSize() const
{
    return _headerFontSize;
}

void SFtpDataModel::setHeaderFontSize(int headerFontSize)
{
    _headerFontSize = headerFontSize;
}

QStringList SFtpDataModel::getHorizontalHeaderData() const
{
    return _horizontalHeaderData;
}

void SFtpDataModel::setHorizontalHeaderData(const QList<QString> &horizontalHeaderData)
{
    _horizontalHeaderData = horizontalHeaderData;
}

QString SFtpDataModel::pointFontFamily() const
{
    return _pointFontFamily;
}

void SFtpDataModel::setPointFontFamily(const QString &pointFontFamily)
{
    _pointFontFamily = pointFontFamily;
}

QString SFtpDataModel::scoreFontFamily() const
{
    return _scoreFontFamily;
}

void SFtpDataModel::setScoreFontFamily(const QString &scoreFontFamily)
{
    _scoreFontFamily = scoreFontFamily;
}

int SFtpDataModel::pointFontSize() const
{
    return _pointFontSize;
}

void SFtpDataModel::setPointFontSize(int pointFontSize)
{
    _pointFontSize = pointFontSize;
}

int SFtpDataModel::scoreFontSize() const
{
    return _scoreFontSize;
}

void SFtpDataModel::setScoreFontSize(int scoreFontSize)
{
    _scoreFontSize = scoreFontSize;
}

int SFtpDataModel::initialValue() const
{
    return _initialValue;
}

void SFtpDataModel::setInitialValue(int initialValue)
{
    _initialValue = initialValue;
    updateInitialCellValues();
}

int SFtpDataModel::minimumRowCount() const
{
    return _minimumRowCount;
}

void SFtpDataModel::setMinimumRowCount(int minimumRowCount)
{
    Q_UNUSED(minimumRowCount);
    return;
}

int SFtpDataModel::minimumColumnCount() const
{
    return _minimumColumnCount;
}

void SFtpDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    Q_UNUSED(minimumColumnCount);
    return;
}

int SFtpDataModel::preferedHeaderItemWidth() const
{
    auto preferedWidth = columnWidthsAt(0);
    return preferedWidth;
}

void SFtpDataModel::setNumberOfAttemps(const int &count)
{
    _attemps = count;
    emit dataChanged(QModelIndex(),QModelIndex());
}

void SFtpDataModel::setColumnCount(const int &count)
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

void SFtpDataModel::setRowCount(const int &count)
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

double SFtpDataModel::scale() const
{
    return _scale;
}

void SFtpDataModel::setScale(double scale)
{
    _scale = scale;
}

int SFtpDataModel::horizontalHeaderFillMode() const
{
    return _horizontalFillMode;
}

void SFtpDataModel::setHorizontalHeaderFillMode(const int &fillMode)
{
    _horizontalFillMode = fillMode;
    emit fillModeChanged();
}

