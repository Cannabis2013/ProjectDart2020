#include "dartspointmulticolumndatamodel.h"

DartsPointMultiColumnDataModel::DartsPointMultiColumnDataModel()
{
    connect(this,&DartsPointMultiColumnDataModel::initialValueChanged,this,&DartsPointMultiColumnDataModel::updateInitialCellValues);
}

QVariant DartsPointMultiColumnDataModel::getData(const int &row, const int &column, const int &mode)
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

int DartsPointMultiColumnDataModel::editData(const int &row, const int &column,
                                               const int &point, const int &score)
{
    if(row < 0 || row >= rowCount())
        return -1;
    else if(column < 0 || column >= columnCount())
        return -1;
    auto index = createIndex(row,column);
    if(!isCellDecorated(index))
        return -1;
    auto oldData = this->data(index,Qt::DisplayRole);
    auto newData = PointInputModel(point,score);
    if(!setData(index,QVariant::fromValue<PointInputModel>((newData)),Qt::DisplayRole))
        return -1;
    return oldData.toInt();
}

bool DartsPointMultiColumnDataModel::insertData(const QString &playerName,
                              const int &point,
                              const int &score)
{
    return appendPlayerData(playerName,point,score,headerOrientation());
}

bool DartsPointMultiColumnDataModel::setPlayerData(const QString &playerName,
                                 const int &point,
                                 const int &score,
                                 const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    auto indexOfPlayer = indexOfHeaderItem(playerName,orientation);
    auto scorePair = PointInputModel(point,score);
    if(orientation == Qt::Horizontal)
    {
        auto modelIndex = this->createIndex(0,indexOfPlayer);

        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,QVariant::fromValue<PointInputModel>(scorePair),Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    else if(orientation == Qt::Vertical)
    {
        auto modelIndex = this->createIndex(indexOfPlayer,0);
        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,QVariant::fromValue<PointInputModel>(scorePair),Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    return true;
}

bool DartsPointMultiColumnDataModel::appendPlayerData(const QString &playerName,
                                                const int &point,
                                                const int &score,
                                                const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    auto index = indexOfHeaderItem(playerName,orientation);
    auto pair = PointInputModel(point,score);
    if(orientation == Qt::Horizontal)
    {
        auto row = index < columnCount() ? rowCount(index) : 0;
        auto modelIndex = this->createIndex(row,index);

        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,QVariant::fromValue<PointInputModel>(pair),Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    else if(orientation == Qt::Vertical)
    {
        auto rowCount = _data.count();
        auto column = index < rowCount ?
                    indexOfLastDecoratedCell(index,orientation) + 1 : 0;
        auto modelIndex = this->createIndex(index,column);
        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,QVariant::fromValue<PointInputModel>(pair),Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    return true;
}

bool DartsPointMultiColumnDataModel::removeLastItem(const QString &playerName, const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    if(orientation == Qt::Horizontal)
    {
        auto column = indexOfHeaderItem(playerName,orientation);
        auto row = indexOfLastDecoratedCell(column,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index) != PointInputModel(-1,-1);
        return result;
    }
    else
    {
        auto row = indexOfHeaderItem(playerName,orientation);
        auto column = indexOfLastDecoratedCell(row,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index) != PointInputModel(-1,-1);
        return result;
    }
}

void DartsPointMultiColumnDataModel::appendHeaderItem(const QVariant &data)
{
    auto glyphLength = stringWidth(data.toString(),
                                   scoreFontFamily(),
                                   headerFontSize());
    if(_verticalHeaderData.count() >= rowCount())
        insertRows(_verticalHeaderData.count(),1,QModelIndex());
    else
        emit dataChanged(QModelIndex(),QModelIndex());
    _verticalHeaderData.append(data.toString());
    if(glyphLength > _verticalHeaderStringWidth)
        setVerticalHeaderStringWidth(glyphLength);
}

void DartsPointMultiColumnDataModel::clearData()
{
    _data.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    _columns = minimumColumnCount();
    _rows = 0;
    _horizontalHeaderData.clear();
    _verticalHeaderData.clear();
    emit dataChanged(createIndex(0,0),bottomRight);
}

QString DartsPointMultiColumnDataModel::getHeaderData(const int &index, const int &headerOrientation) const
{
    auto orientation = headerOrientation != -1 ? headerOrientation :
                                                 this->headerOrientation();
    auto value = headerData(index,static_cast<Qt::Orientation>(orientation),Qt::DisplayRole).toString();
    return value;
}

int DartsPointMultiColumnDataModel::headerItemCount(const int &headerOrientation) const
{
    auto orientation = headerOrientation != -1 ?
                headerOrientation : this->headerOrientation();
    if(orientation == Qt::Horizontal)
    {
        if(horizontalHeaderFillMode() == HeaderFillMode::FixedStrings)
            return _horizontalHeaderData.count();
        else
            return columnCount();
    }
    else
    {
        if(verticalHeaderFillMode() == HeaderFillMode::FixedStrings)
            return _verticalHeaderData.count();
        else
            return rowCount();
    }
}

int DartsPointMultiColumnDataModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int DartsPointMultiColumnDataModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double DartsPointMultiColumnDataModel::columnWidthAt(const int &column) const
{
    auto s = scale();
    auto w = columnWidthsAt(column);
    auto columnWidth = s*w;
    if(columnWidth < minimumPreferedColumnWidth)
        return minimumPreferedColumnWidth;
    else
        return columnWidth;
}

double DartsPointMultiColumnDataModel::rowHeightAt(const int &row) const
{
    if(_data.count() <= 0)
        return 0;

    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),scoreFontSize()));
    auto pointFontmetric = QFontMetrics(QFont(pointFontFamily(),pointFontSize()));

    QString headerString;

    if(_verticalHeaderData.count() <= row)
    {
        if(verticalHeaderFillMode() == HeaderFillMode::DynamicNumerics)
            headerString = QString::number(row + 1);
        else
            return minimumPreferedRowHeight;
    }
    else
        headerString = _verticalHeaderData.at(row);

    auto resultingGlyphLenght = scoreFontMetric.boundingRect(headerString).height();
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

    if(resultingGlyphLenght < minimumPreferedRowHeight)
        resultingGlyphLenght = minimumPreferedRowHeight;

    return resultingGlyphLenght;
}

int DartsPointMultiColumnDataModel::horizontalHeaderCount() const
{
    return _horizontalHeaderData.count();
}

int DartsPointMultiColumnDataModel::verticalHeaderCount() const
{
    return _verticalHeaderData.count();
}

int DartsPointMultiColumnDataModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int DartsPointMultiColumnDataModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

void DartsPointMultiColumnDataModel::setColumnWidthAt(const int &column, const double &w)
{
    _columnWidths.replace(column,w);
}

int DartsPointMultiColumnDataModel::columnWidthsAt(const int &index) const
{
    auto columnWidth = _columnWidths.at(index);
    return columnWidth;
}

QVariant DartsPointMultiColumnDataModel::data(const QModelIndex &index, int role) const
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

QVariant DartsPointMultiColumnDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    auto roundIndex = (section - 1)/_attemps + 1;

    if(orientation == Qt::Horizontal){
        if(horizontalHeaderFillMode() == HeaderFillMode::DynamicNumerics)
        {
            if(appendMode() == AppendDataMode::MultiAppend)
                return section != 0 ? QVariant(roundIndex) : initialValue();
            else if(appendMode() == AppendDataMode::SingleAppend)
                return QVariant(roundIndex);
        }
        else if(horizontalHeaderFillMode() == HeaderFillMode::FixedStrings &&
                section < horizontalHeaderCount())
        {
            return _horizontalHeaderData.at(section);
        }
        else
            return QVariant();
    }
    else if(orientation == Qt::Vertical)
    {
        if(verticalHeaderFillMode() == HeaderFillMode::DynamicNumerics)
        {
            if(appendMode() == AppendDataMode::MultiAppend)
                return section != 0 ? QVariant(roundIndex) : initialValue();
            else if(appendMode() == AppendDataMode::SingleAppend)
                return QVariant(roundIndex);
        }
        if(verticalHeaderFillMode() == HeaderFillMode::FixedStrings &&
                section < verticalHeaderCount())
        {
            return _verticalHeaderData.at(section);
        }
        return QVariant();
    }
    return QVariant();
}

int DartsPointMultiColumnDataModel::numberOfAttemps() const
{
    return _attemps;
}

bool DartsPointMultiColumnDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto row = index.row();
    auto column = index.column();

    if(row < 0 || column < 0)
        return false;

    if(row >= rowCount())
    {
        auto deltaR = appendMode() != AppendDataMode::SingleAppend ?
                    numberOfAttemps() : 1;
        insertRows(row,deltaR,QModelIndex());
    }

    if(column >= columnCount())
    {
        auto deltaC = appendMode() != AppendDataMode::SingleAppend ?
                    numberOfAttemps() : 1;
        insertColumns(column,deltaC,QModelIndex());
    }

    auto pairs = _data.at(row);
    auto newPair = value.value<PointInputModel>();
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

bool DartsPointMultiColumnDataModel::insertRows(int row, int count, const QModelIndex &)
{
    auto firstRow = row <= rowCount(QModelIndex()) ? row : rowCount(QModelIndex()) - 1;
    auto lastRow  =  row <= rowCount(QModelIndex()) ? firstRow + count : 2*row + count - firstRow;
    auto c = row <= rowCount(QModelIndex()) ? count : count + (row - firstRow) - 1;

    beginInsertRows(QModelIndex(),firstRow,lastRow);

    for (int i = 0; i < c; ++i) {
        auto initializedDataRow = [this]
        {
            LinkedList<PointInputModel> resultingList;
            auto count = columnCount(QModelIndex(QModelIndex()));
            for (int i = 0; i < count; ++i)
                resultingList << PointInputModel(-1,-1);
            return resultingList;
        }();
        _data.insert(row,initializedDataRow);
    }

    endInsertRows();

    _rows += c;

    emit dataChanged(createIndex(row,0),createIndex(lastRow,columnCount()));

    return true;
}

bool DartsPointMultiColumnDataModel::insertColumns(int column, int count, const QModelIndex &)
{
    auto firstColumn = column <= columnCount() ? column : columnCount() - 1;
    auto lastColumn  =  column <= columnCount() ? firstColumn + count : 2*column + count - firstColumn;
    auto c = column <= columnCount() ? count : count + (column - firstColumn) - 1;

    beginInsertColumns(QModelIndex(),firstColumn,lastColumn);

    for (int i = 0;i<_data.count();i++) {
        auto columnsData = _data.at(i);
        LinkedList<PointInputModel> columnsDataIndice;
        for (int i = 0; i < c; ++i)
            columnsDataIndice << PointInputModel(-1,-1);
        columnsData.insert(column,columnsDataIndice);
        _data.replace(i,columnsData);
    }

    QList<double> newColumnWidths;
    for (int i = 0; i < c; ++i)
        newColumnWidths << minimumPreferedColumnWidth;

    for (int i = 0; i < newColumnWidths.count(); ++i) {
        auto columnWidth = newColumnWidths.at(i);
        _columnWidths.insert(column,columnWidth);
    }
    endInsertColumns();
    _columns += c;
    emit dataChanged(createIndex(0,firstColumn),
                     createIndex(headerItemCount(0x2),lastColumn));
    return true;
}

bool DartsPointMultiColumnDataModel::removeRows(int row, int count, const QModelIndex &)
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
        _data.removeAt(i);
        // Remove corresponding header rows
        _verticalHeaderData.removeAt(i);
    }

    endRemoveRows();

    _rows -= count;

    // Notify model and surrounding state that data has changed
    emit dataChanged(topLeftIndex,bottomRightIndex,{Qt::DisplayRole});

    return true;
}

bool DartsPointMultiColumnDataModel::removeColumns(int column, int count, const QModelIndex &)
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

void DartsPointMultiColumnDataModel::updateInitialCellValues()
{

    if(_data.count() < 1)
        return;
    auto orientation = _headerOrientation;
    auto initialValue = this->initialValue();
    if(orientation == Qt::Horizontal)
    {
        auto firstColumn = _data.at(0);
        if(firstColumn.count() < 1)
            return;
        for (int i = 0; i < firstColumn.count(); ++i)
            setData(createIndex(0,i),initialValue,Qt::DisplayRole);
    }
    else
    {
        for (int rowIndex = 0; rowIndex < rowCount(); ++rowIndex) {
            setData(createIndex(rowIndex,0),initialValue,Qt::DisplayRole);
        }
    }
}

bool DartsPointMultiColumnDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int DartsPointMultiColumnDataModel::indexOfLastDecoratedCell(const int &index,const int &orientation)
{
    if(orientation == Qt::Vertical)
    {
        if(index >= _data.count() || index < 0)
            return -1;
        auto columnsData = _data.at(index);

        for (int col = 0; col < columnCount(QModelIndex()); ++col) {
            auto columnData = columnsData.at(col);
            auto point = columnData.first;

            if(point == -1)
                return col - 1;
        }

        return columnCount() - 1;
    }
    else if(orientation == Qt::Horizontal)
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
    else
    {
        return -1;
    }
}

int DartsPointMultiColumnDataModel::rowCount(const int &column)
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

bool DartsPointMultiColumnDataModel::isColumnEmpty(const int &col)
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

bool DartsPointMultiColumnDataModel::isRowEmpty(const int &row)
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

QPair<int, int> DartsPointMultiColumnDataModel::removeData(const QModelIndex &index)
{
    if(!index.isValid())
        return PointInputModel(-1,-1);
    auto row = index.row();
    auto column = index.column();
    auto columnData = _data.at(row);
    auto data = columnData.at(column);
    auto initialPair = PointInputModel(-1,-1);

    columnData.replace(column,initialPair);
    _data.replace(row,columnData);
    if(headerOrientation() == Qt::Vertical)
    {
        if(isColumnEmpty(column) && column > minimumColumnCount())
        {
            removeColumns(column,1,QModelIndex());
            return data;
        }
    }
    else
    {
        if(isRowEmpty(row) && row > minimumRowCount())
        {
            removeColumns(column,1,QModelIndex());
            return data;
        }
    }

    emit dataChanged(createIndex(row,column),createIndex(row,column));
    return data;
}

int DartsPointMultiColumnDataModel::indexOfHeaderItem(const QString &data, const int &orientation)
{
    if(orientation == Qt::Vertical)
    {
        auto index = _verticalHeaderData.indexOf(data);
        return index;
    }
    else
    {
        auto index = _horizontalHeaderData.indexOf(data);
        return index;
    }
}

int DartsPointMultiColumnDataModel::stringWidth(const QString &string, const QString &family, const int &pointSize) const
{
    auto fontMetric = QFontMetrics(QFont(family,pointSize));
    auto r = fontMetric.boundingRect(string).width();
    return r;
}

void DartsPointMultiColumnDataModel::setVerticalHeaderStringWidth(double verticalHeaderStringWidth)
{
    _verticalHeaderStringWidth = verticalHeaderStringWidth;
}

int DartsPointMultiColumnDataModel::headerFontSize() const
{
    return _headerFontSize;
}

void DartsPointMultiColumnDataModel::setHeaderFontSize(int headerFontSize)
{
    _headerFontSize = headerFontSize;
}

QStringList DartsPointMultiColumnDataModel::getHorizontalHeaderData() const
{
    return _horizontalHeaderData;
}

void DartsPointMultiColumnDataModel::setHorizontalHeaderData(const QList<QString> &horizontalHeaderData)
{
    _horizontalHeaderData = horizontalHeaderData;
}

QStringList DartsPointMultiColumnDataModel::getVerticalHeaderData() const
{
    return _verticalHeaderData;
}

void DartsPointMultiColumnDataModel::setVerticalHeaderData(const QList<QString> &verticalHeaderData)
{
    _verticalHeaderData = verticalHeaderData;
}

int DartsPointMultiColumnDataModel::appendMode() const
{
    return _appendMode;
}

void DartsPointMultiColumnDataModel::setAppendMode(int appendMode)
{
    _appendMode = appendMode;
}

QString DartsPointMultiColumnDataModel::pointFontFamily() const
{
    return _pointFontFamily;
}

void DartsPointMultiColumnDataModel::setPointFontFamily(const QString &pointFontFamily)
{
    _pointFontFamily = pointFontFamily;
}

QString DartsPointMultiColumnDataModel::scoreFontFamily() const
{
    return _scoreFontFamily;
}

void DartsPointMultiColumnDataModel::setScoreFontFamily(const QString &scoreFontFamily)
{
    _scoreFontFamily = scoreFontFamily;
}

int DartsPointMultiColumnDataModel::pointFontSize() const
{
    return _pointFontSize;
}

void DartsPointMultiColumnDataModel::setPointFontSize(int pointFontSize)
{
    _pointFontSize = pointFontSize;
}

int DartsPointMultiColumnDataModel::scoreFontSize() const
{
    return _scoreFontSize;
}

void DartsPointMultiColumnDataModel::setScoreFontSize(int scoreFontSize)
{
    _scoreFontSize = scoreFontSize;
}

int DartsPointMultiColumnDataModel::initialValue() const
{
    return _initialValue;
}

void DartsPointMultiColumnDataModel::setInitialValue(int initialValue)
{
    _initialValue = initialValue;
    emit initialValueChanged();
}

int DartsPointMultiColumnDataModel::minimumRowCount() const
{
    return _minimumRowCount;
}

void DartsPointMultiColumnDataModel::setMinimumRowCount(int minimumRowCount)
{
    if(appendMode() == AppendDataMode::SingleAppend)
        return;
    _minimumRowCount = minimumRowCount;
    auto rowCount = this->rowCount();
    if(minimumRowCount > rowCount)
        setRowCount(minimumRowCount);
}

int DartsPointMultiColumnDataModel::minimumColumnCount() const
{
    return _minimumColumnCount;
}

void DartsPointMultiColumnDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    if(appendMode() == AppendDataMode::SingleAppend)
        return;
    _minimumColumnCount = minimumColumnCount;
    auto colCount = columnCount();
    if(minimumColumnCount > colCount)
        setColumnCount(minimumColumnCount);
    emit minimumColumnCountChanged();
}

int DartsPointMultiColumnDataModel::headerOrientation() const
{
    return _headerOrientation;
}

void DartsPointMultiColumnDataModel::setHeaderOrientation(int headerOrientation)
{
    _headerOrientation = headerOrientation;
}

int DartsPointMultiColumnDataModel::preferedHeaderItemWidth() const
{
    return _verticalHeaderStringWidth;
}

void DartsPointMultiColumnDataModel::setNumberOfAttemps(const int &count)
{
    _attemps = count;
    emit dataChanged(QModelIndex(),QModelIndex());
}

void DartsPointMultiColumnDataModel::setColumnCount(const int &count)
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

void DartsPointMultiColumnDataModel::setRowCount(const int &count)
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

double DartsPointMultiColumnDataModel::scale() const
{
    return _scale;
}

void DartsPointMultiColumnDataModel::setScale(double scale)
{
    _scale = scale;
}

int DartsPointMultiColumnDataModel::horizontalHeaderFillMode() const
{
    return _horizontalFillMode;
}

int DartsPointMultiColumnDataModel::verticalHeaderFillMode() const
{
    return _verticalFillMode;
}

void DartsPointMultiColumnDataModel::setHorizontalHeaderFillMode(const int &fillMode)
{
    _horizontalFillMode = fillMode;
    emit fillModeChanged();
}

void DartsPointMultiColumnDataModel::setVerticalHeaderFillMode(const int &fillMode)
{
    _verticalFillMode = fillMode;
    emit fillModeChanged();
}
