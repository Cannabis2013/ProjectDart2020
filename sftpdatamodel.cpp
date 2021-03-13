#include "sftpdatamodel.h"

SFTPDataModel::SFTPDataModel()
{
    connect(this,&SFTPDataModel::initialValueChanged,this,&SFTPDataModel::updateInitialCellValues);
}

QVariant SFTPDataModel::getData(const int &row, const int &column, const int &mode)
{
    if(row >= rowCount() || column >= columnCount())
        return -1;
    auto columnsData = _data.at(row);
    auto columnData = columnsData.at(column);
    auto pointValue = columnData.first;
    auto scoreValue = columnData.second;
    auto result = mode == 0x1 ? pointValue : scoreValue;
    if(result == -1)
        return "-";
    else
        return result;
}

int SFTPDataModel::editData(const int &row, const int &column, const int &point, const int &score)
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

bool SFTPDataModel::insertData(const QString &playerName,
                                         const int &point,
                                         const int &score)
{
    return setPlayerData(playerName,point,score);;
}

bool SFTPDataModel::setPlayerData(const QString &playerName,
                                 const int &point,
                                 const int &score)
{
    auto indexOfPlayer = indexOfHeaderItem(playerName);
    auto scorePair = scoreModel(point,score);
    auto modelIndex = this->createIndex(0,indexOfPlayer);

    if(!modelIndex.isValid())
        return false;
    try {
        setData(modelIndex,QVariant::fromValue<scoreModel>(scorePair),Qt::DisplayRole);
    } catch (std::out_of_range *e) {
        printf("%s\n",e->what());
        return false;
    }
    return true;
}

bool SFTPDataModel::removeLastItem(const QString &playerName)
{
    auto column = indexOfHeaderItem(playerName);
    auto row = indexOfLastDecoratedCell(column);
    auto index = createIndex(row,column);
    auto result = removeData(index) != scoreModel(-1,-1);
    return result;
}

void SFTPDataModel::appendHeaderItem(const QVariant &data)
{
    auto glyphLength = stringWidth(data.toString(),
                                   scoreFontFamily(),
                                   headerFontSize());
    if(_horizontalHeaderData.count() >= columnCount())
        insertColumns(_horizontalHeaderData.count(),1,QModelIndex());
    else
        emit dataChanged(QModelIndex(),QModelIndex());
    _horizontalHeaderData.append(data.toString());
    auto column = _horizontalHeaderData.count() - 1;
    if(glyphLength > columnWidthsAt(column))
        setColumnWidthAt(column,glyphLength);
}

void SFTPDataModel::clearData()
{
    _data.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    _columns = 0;
    _rows = 0;

    _horizontalHeaderData.clear();

    emit dataChanged(createIndex(0,0),bottomRight);
}

QString SFTPDataModel::getHeaderData(const int &index) const
{
    auto value = headerData(index,Qt::Horizontal,Qt::DisplayRole).toString();
    return value;
}

int SFTPDataModel::headerItemCount() const
{
    if(horizontalHeaderFillMode() == HeaderFillMode::FixedStrings)
        return _horizontalHeaderData.count();
    else
        return columnCount();
}

int SFTPDataModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int SFTPDataModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double SFTPDataModel::columnWidthAt(const int &column) const
{
    auto s = scale();
    auto w = columnWidthsAt(column);
    auto columnWidth = s*w;
    if(columnWidth < SingleFTPDataModel::minimumPreferedColumnWidth)
        return SingleFTPDataModel::minimumPreferedColumnWidth;
    else
        return columnWidth;
}

double SFTPDataModel::rowHeightAt(const int &row) const
{
    if(_data.count() <= 0)
        return 0;

    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),scoreFontSize()));
    auto pointFontmetric = QFontMetrics(QFont(pointFontFamily(),pointFontSize()));

    auto resultingGlyphLenght = 0;
    auto count = columnCount();
    for (int c = 0; c < count; ++c) {
        auto columnsData = _data.at(row);
        auto columnsDataCount = columnsData.count();
        if(columnsDataCount != columnCount())
            return 0;
        auto columnData = columnsData.at(c);
        auto point = columnData.first;
        auto score = columnData.second;
        auto pointString = QString::number(point);
        auto scoreString = QString::number(score);
        auto scoreGlyphHeight = scoreFontMetric.boundingRect(scoreString).height();
        auto pointGlyphHeight = pointFontmetric.boundingRect(pointString).height();
        auto totalGlypHeight = scoreGlyphHeight + pointGlyphHeight;
        resultingGlyphLenght = totalGlypHeight > resultingGlyphLenght ? totalGlypHeight : resultingGlyphLenght;
    }

    if(resultingGlyphLenght < SingleFTPDataModel::minimumPreferedRowHeight)
        resultingGlyphLenght = SingleFTPDataModel::minimumPreferedRowHeight;

    return resultingGlyphLenght;
}

int SFTPDataModel::horizontalHeaderCount() const
{
    return _horizontalHeaderData.count();
}

int SFTPDataModel::verticalHeaderCount() const
{
    return 0;
}

int SFTPDataModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int SFTPDataModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

void SFTPDataModel::setColumnWidthAt(const int &column, const double &w)
{
    _columnWidths.replace(column,w);
}

int SFTPDataModel::columnWidthsAt(const int &index) const
{
    auto columnWidth = _columnWidths.at(index);
    return columnWidth;
}

QVariant SFTPDataModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || _data.count() <= 0)
        return QVariant();
    auto row = index.row();
    auto column = index.column();
    auto pairs = _data.at(row);
    if(index.column() >= pairs.count())
        return QVariant();
    if(role != Qt::DisplayRole)
        return QVariant();

    auto pair = pairs.at(column);
    auto pointValue = pair.first;
    auto scoreValue = pair.second;
    auto data = QString::number(pointValue) + " " + QString::number(scoreValue);
    return scoreValue >= 0 ?
                QVariant(data) :
                QVariant("");
}

QVariant SFTPDataModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int SFTPDataModel::numberOfAttemps() const
{
    return _attemps;
}

bool SFTPDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto row = index.row();
    auto column = index.column();

    if(row < 0 || column < 0)
        return false;

    if(row >= rowCount())
        insertRows(row,1,QModelIndex());

    if(column >= columnCount())
        insertColumns(column,1,QModelIndex());

    auto pairs = _data.at(row);
    auto newPair = value.value<scoreModel>();
    pairs.replace(column,newPair);
    _data.replace(row,pairs);

    auto pointGlypWidth = stringWidth(QString::number(newPair.first),
                                      pointFontFamily(),
                                      pointFontSize());
    auto scoreGlypWidth = stringWidth(QString::number(newPair.second),
                                      scoreFontFamily(),
                                      scoreFontSize());
    int totalGlyphWidth = pointGlypWidth + scoreGlypWidth;
    if(totalGlyphWidth > columnWidthsAt(column))
        setColumnWidthAt(column,totalGlyphWidth);

    emit dataChanged(index,index,{role});

    return true;
}

bool SFTPDataModel::insertRows(int row, int count, const QModelIndex &)
{
    auto firstRow = row <= rowCount(QModelIndex()) ? row : rowCount(QModelIndex()) - 1;
    auto lastRow  =  row <= rowCount(QModelIndex()) ? firstRow + count : 2*row + count - firstRow;
    auto c = row <= rowCount(QModelIndex()) ? count : count + (row - firstRow) - 1;

    beginInsertRows(QModelIndex(),firstRow,lastRow);

    for (int i = 0; i < c; ++i) {
        auto initializedDataRow = [this]
        {
            LinkedList<scoreModel> resultingList;
            auto count = columnCount(QModelIndex(QModelIndex()));
            for (int i = 0; i < count; ++i)
                resultingList << scoreModel(-1,-1);
            return resultingList;
        }();
        _data.insert(row,initializedDataRow);
    }

    endInsertRows();

    _rows += c;

    emit dataChanged(createIndex(row,0),createIndex(lastRow,columnCount()));

    return true;
}

bool SFTPDataModel::insertColumns(int column, int count, const QModelIndex &)
{
    auto firstColumn = column <= columnCount() ? column : columnCount() - 1;
    auto lastColumn  =  column <= columnCount() ? firstColumn + count : 2*column + count - firstColumn;
    auto c = column <= columnCount() ? count : count + (column - firstColumn) - 1;

    beginInsertColumns(QModelIndex(),firstColumn,lastColumn);

    for (int i = 0;i<_data.count();i++) {
        auto columnsData = _data.at(i);
        LinkedList<scoreModel> columnsDataIndice;
        for (int i = 0; i < c; ++i)
            columnsDataIndice << scoreModel(-1,-1);
        columnsData.insert(column,columnsDataIndice);
        _data.replace(i,columnsData);
    }

    QList<double> newColumnWidths;
    for (int i = 0; i < c; ++i)
        newColumnWidths << SingleFTPDataModel::minimumPreferedColumnWidth;

    for (int i = 0; i < newColumnWidths.count(); ++i) {
        auto columnWidth = newColumnWidths.at(i);
        _columnWidths.insert(column,columnWidth);
    }
    endInsertColumns();
    _columns += c;
    emit dataChanged(createIndex(0,firstColumn),
                     createIndex(headerItemCount(),lastColumn));
    return true;
}

bool SFTPDataModel::removeRows(int row, int count, const QModelIndex &)
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

bool SFTPDataModel::removeColumns(int column, int count, const QModelIndex &)
{
    // Check if input satisfies model constraints
    if(column < 0 || column >= columnCount())
        return false;

    // Begin remove columns
    auto limit = column + count;
    beginRemoveColumns(QModelIndex(),column,column + count);

    for (int i = 0; i < _data.count(); ++i) {
        auto row = _data.at(i);
        for (int j = column; j < limit; ++j)
            row.removeAt(j);
        _data.replace(i,row);
    }

    _columns -= count;
    endRemoveColumns();
    emit dataChanged(QModelIndex(),QModelIndex());

    return true;
}

void SFTPDataModel::updateInitialCellValues()
{

    if(_data.count() < 1)
        return;
    auto initialValue = this->initialValue();
    auto firstColumn = _data.at(0);
    if(firstColumn.count() < 1)
        return;
    for (int i = 0; i < firstColumn.count(); ++i)
        setData(createIndex(0,i),initialValue,Qt::DisplayRole);
}

bool SFTPDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int SFTPDataModel::indexOfLastDecoratedCell(const int &index)
{
    for (int row = 0; row < rowCount(); ++row) {
        auto pairs = _data.at(row);
        auto pair = pairs.at(index);
        auto score = pair.first;
        if(score == -1)
        {
            return row - 1;
        }
    }
    return rowCount() - 1;
}

int SFTPDataModel::rowCount(const int &column)
{
    for (int row = 0; row < _data.count(); ++row) {
        auto scoreModels = _data.at(row);
        auto scoreModel = scoreModels.at(column);
        auto point = scoreModel.first;
        auto scoreModelsCount = scoreModels.count();
        if(scoreModelsCount > column && point == -1)
            return row;
    }
    return rowCount();
}

bool SFTPDataModel::isColumnEmpty(const int &col)
{
    if(col < 0 || col >= columnCount())
        throw std::out_of_range("Index out of range");

    for (auto pairsRow : _data) {
        auto pair = pairsRow.at(col);
        auto point = pair.first;
        if(point != -1)
            return false;
    }
    return true;
}

bool SFTPDataModel::isRowEmpty(const int &row)
{
    if(row < 0 || row >= rowCount())
        throw std::out_of_range("Index out of range");
    auto columnsData = _data.at(row);
    for (int i = 0; i < columnsData.count(); ++i) {
        auto columnData = columnsData.at(i);
        auto point = columnData.first;
        if(point != -1)
            return false;
    }
    return true;
}

QPair<int, int> SFTPDataModel::removeData(const QModelIndex &index)
{
    if(!index.isValid())
        return scoreModel(-1,-1);
    auto row = index.row();
    auto column = index.column();
    auto columnData = _data.at(row);
    auto data = columnData.at(column);
    auto initialPair = scoreModel(-1,-1);

    columnData.replace(column,initialPair);
    _data.replace(row,columnData);
    if(isRowEmpty(row) && row > minimumRowCount())
    {
        removeColumns(column,1,QModelIndex());
        return data;
    }

    emit dataChanged(createIndex(row,column),createIndex(row,column));
    return data;
}

int SFTPDataModel::indexOfHeaderItem(const QString &data)
{
    auto index = _horizontalHeaderData.indexOf(data);
    return index;
}

int SFTPDataModel::stringWidth(const QString &string, const QString &family, const int &pointSize) const
{
    auto fontMetric = QFontMetrics(QFont(family,pointSize));
    auto r = fontMetric.boundingRect(string).width();
    return r;
}

int SFTPDataModel::headerFontSize() const
{
    return _headerFontSize;
}

void SFTPDataModel::setHeaderFontSize(int headerFontSize)
{
    _headerFontSize = headerFontSize;
}

QStringList SFTPDataModel::getHorizontalHeaderData() const
{
    return _horizontalHeaderData;
}

void SFTPDataModel::setHorizontalHeaderData(const QList<QString> &horizontalHeaderData)
{
    _horizontalHeaderData = horizontalHeaderData;
}

QString SFTPDataModel::pointFontFamily() const
{
    return _pointFontFamily;
}

void SFTPDataModel::setPointFontFamily(const QString &pointFontFamily)
{
    _pointFontFamily = pointFontFamily;
}

QString SFTPDataModel::scoreFontFamily() const
{
    return _scoreFontFamily;
}

void SFTPDataModel::setScoreFontFamily(const QString &scoreFontFamily)
{
    _scoreFontFamily = scoreFontFamily;
}

int SFTPDataModel::pointFontSize() const
{
    return _pointFontSize;
}

void SFTPDataModel::setPointFontSize(int pointFontSize)
{
    _pointFontSize = pointFontSize;
}

int SFTPDataModel::scoreFontSize() const
{
    return _scoreFontSize;
}

void SFTPDataModel::setScoreFontSize(int scoreFontSize)
{
    _scoreFontSize = scoreFontSize;
}

int SFTPDataModel::initialValue() const
{
    return _initialValue;
}

void SFTPDataModel::setInitialValue(int initialValue)
{
    _initialValue = initialValue;
    emit initialValueChanged();
}

int SFTPDataModel::minimumRowCount() const
{
    return _minimumRowCount;
}

void SFTPDataModel::setMinimumRowCount(int minimumRowCount)
{
    Q_UNUSED(minimumRowCount);
    return;
}

int SFTPDataModel::minimumColumnCount() const
{
    return _minimumColumnCount;
}

void SFTPDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    Q_UNUSED(minimumColumnCount);
    return;
}

int SFTPDataModel::preferedHeaderItemWidth() const
{
    auto preferedWidth = columnWidthsAt(0);
    return preferedWidth;
}

void SFTPDataModel::setNumberOfAttemps(const int &count)
{
    _attemps = count;
    emit dataChanged(QModelIndex(),QModelIndex());
}

void SFTPDataModel::setColumnCount(const int &count)
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
}

void SFTPDataModel::setRowCount(const int &count)
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

double SFTPDataModel::scale() const
{
    return _scale;
}

void SFTPDataModel::setScale(double scale)
{
    _scale = scale;
}

int SFTPDataModel::horizontalHeaderFillMode() const
{
    return _horizontalFillMode;
}

void SFTPDataModel::setHorizontalHeaderFillMode(const int &fillMode)
{
    _horizontalFillMode = fillMode;
    emit fillModeChanged();
}

