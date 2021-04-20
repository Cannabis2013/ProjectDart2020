#include "sftpdatamodel.h"

SFtpDataModel::SFtpDataModel()
{
    connect(this,&SFtpDataModel::initialValueChanged,this,&SFtpDataModel::updateInitialCellValues);
}

QVariant SFtpDataModel::getData(const int &row, const int &column, const int &mode)
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
    return setPlayerData(playerName,point,score);;
}

bool SFtpDataModel::setPlayerData(const QString &playerName,
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

bool SFtpDataModel::removeLastItem(const QString &playerName)
{
    auto column = indexOfHeaderItem(playerName);
    auto row = indexOfLastDecoratedCell(column);
    auto index = createIndex(row,column);
    auto result = removeData(index) != scoreModel(-1,-1);
    return result;
}

void SFtpDataModel::appendHeaderItem(const QVariant &data)
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
        return _horizontalHeaderData.count();
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
    if(columnWidth < SingleFtpDataModel::minimumPreferedColumnWidth)
        return SingleFtpDataModel::minimumPreferedColumnWidth;
    else
        return columnWidth;
}

double SFtpDataModel::rowHeightAt(const int &row) const
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

    if(resultingGlyphLenght < SingleFtpDataModel::minimumPreferedRowHeight)
        resultingGlyphLenght = SingleFtpDataModel::minimumPreferedRowHeight;

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

bool SFtpDataModel::insertRows(int row, int count, const QModelIndex &)
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

bool SFtpDataModel::insertColumns(int column, int count, const QModelIndex &)
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
        newColumnWidths << SingleFtpDataModel::minimumPreferedColumnWidth;

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

void SFtpDataModel::updateInitialCellValues()
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

bool SFtpDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int SFtpDataModel::indexOfLastDecoratedCell(const int &index)
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

int SFtpDataModel::rowCount(const int &column)
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

bool SFtpDataModel::isColumnEmpty(const int &col)
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

bool SFtpDataModel::isRowEmpty(const int &row)
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

QPair<int, int> SFtpDataModel::removeData(const QModelIndex &index)
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

int SFtpDataModel::indexOfHeaderItem(const QString &data)
{
    auto index = _horizontalHeaderData.indexOf(data);
    return index;
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
    emit initialValueChanged();
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

