#include "dartsmultiscoredatamodel.h"

DartsMultiScoreDataModel::DartsMultiScoreDataModel()
{
    connect(this,&DartsMultiScoreDataModel::initialValueChanged,this,&DartsMultiScoreDataModel::updateInitialCellValues);
}

int DartsMultiScoreDataModel::editData(const int &row, const int &column, const int &score)
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

bool DartsMultiScoreDataModel::insertData(const QString &playerName,
                                          const int &score)
{
    if(appendMode() == AppendDataMode::SingleAppend)
        return setPlayerData(playerName,score,headerOrientation());
    else
        return appendPlayerData(playerName,score,headerOrientation());

    return false;
}

bool DartsMultiScoreDataModel::setPlayerData(const QString &playerName,
                                 const int &score,
                                 const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    auto indexOfPlayer = indexOfHeaderItem(playerName,orientation);
    if(orientation == Qt::Horizontal)
    {
        auto modelIndex = this->createIndex(0,indexOfPlayer);

        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,score,Qt::DisplayRole);
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
            setData(modelIndex,score,Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    return true;
}

bool DartsMultiScoreDataModel::appendPlayerData(const QString &playerName,
                                const int &score,
                                const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    auto index = indexOfHeaderItem(playerName,orientation);
    if(orientation == Qt::Horizontal)
    {
        auto row = index < columnCount() ? rowCount(index) : 0;
        auto modelIndex = this->createIndex(row,index);

        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,score,Qt::DisplayRole);
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
            setData(modelIndex,score,Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    return true;
}

bool DartsMultiScoreDataModel::removeLastItem(const QString &playerName, const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    if(orientation == Qt::Horizontal)
    {
        auto column = indexOfHeaderItem(playerName,orientation);
        auto row = indexOfLastDecoratedCell(column,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index) != -1;
        return result;
    }
    else
    {
        auto row = indexOfHeaderItem(playerName,orientation);
        auto column = indexOfLastDecoratedCell(row,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index) != -1;
        return result;
    }
}

void DartsMultiScoreDataModel::appendHeaderItem(const QVariant &data,
                                            const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ?
                headerOrientation : this->headerOrientation();
    auto glyphLength = stringWidth(data.toString(),
                                   scoreFontFamily(),
                                   headerFontSize());
    if(orientation == Qt::Horizontal){
        if(_horizontalHeaderData.count() >= columnCount())
            insertColumns(_horizontalHeaderData.count(),1,QModelIndex());
        else
            emit dataChanged(QModelIndex(),QModelIndex());
        _horizontalHeaderData.append(data.toString());
        auto column = _horizontalHeaderData.count() - 1;
        if(glyphLength > columnWidthsAt(column))
            setColumnWidthAt(column,glyphLength);
    }
    else{
        if(_verticalHeaderData.count() >= rowCount())
            insertRows(_verticalHeaderData.count(),1,QModelIndex());
        else
            emit dataChanged(QModelIndex(),QModelIndex());
        _verticalHeaderData.append(data.toString());
        if(glyphLength > columnWidthsAt(0))
            setColumnWidthAt(0,glyphLength);
    }
}

void DartsMultiScoreDataModel::clearData()
{
    _data.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    _columns = 0;
    _rows = 0;

    _horizontalHeaderData.clear();
    _verticalHeaderData.clear();

    emit dataChanged(createIndex(0,0),bottomRight);
}

QString DartsMultiScoreDataModel::getHeaderData(const int &index, const int &headerOrientation) const
{
    auto orientation = headerOrientation != -1 ? headerOrientation :
                                                 this->headerOrientation();
    auto value = headerData(index,static_cast<Qt::Orientation>(orientation),Qt::DisplayRole).toString();
    return value;
}

int DartsMultiScoreDataModel::headerItemCount(const int &headerOrientation) const
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

int DartsMultiScoreDataModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int DartsMultiScoreDataModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double DartsMultiScoreDataModel::columnWidthAt(const int &column) const
{
    auto s = scale();
    auto w = columnWidthsAt(column);
    auto columnWidth = s*w;
    if(columnWidth < minimumPreferedColumnWidth)
        return minimumPreferedColumnWidth;
    else
        return columnWidth;
}

double DartsMultiScoreDataModel::rowHeightAt(const int &row) const
{
    if(_data.count() <= 0)
        return 0;
    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),scoreFontSize()));
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
        auto score = columnsData.at(c);
        auto scoreString = QString::number(score);
        auto scoreGlyphHeight = scoreFontMetric.boundingRect(scoreString).height();
        resultingGlyphLenght = scoreGlyphHeight > resultingGlyphLenght ? scoreGlyphHeight :
                                                                         resultingGlyphLenght;
    }

    if(resultingGlyphLenght < minimumPreferedRowHeight)
        resultingGlyphLenght = minimumPreferedRowHeight;

    return resultingGlyphLenght;
}

int DartsMultiScoreDataModel::horizontalHeaderCount() const
{
    return _horizontalHeaderData.count();
}

int DartsMultiScoreDataModel::verticalHeaderCount() const
{
    return _verticalHeaderData.count();
}

int DartsMultiScoreDataModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int DartsMultiScoreDataModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

void DartsMultiScoreDataModel::setColumnWidthAt(const int &column, const double &w)
{
    _columnWidths.replace(column,w);
}

int DartsMultiScoreDataModel::columnWidthsAt(const int &index) const
{
    auto columnWidth = _columnWidths.at(index);
    return columnWidth;
}

QVariant DartsMultiScoreDataModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || _data.count() <= 0)
        return QVariant();
    auto row = index.row();
    auto column = index.column();
    auto scoresAtRow = _data.at(row);
    if(index.column() >= scoresAtRow.count())
        return QVariant();
    if(role != Qt::DisplayRole)
        return QVariant();

    auto score = scoresAtRow.at(column);
    auto data =  QString::number(score);
    return score >= 0 ?
                QVariant(data) :
                QVariant("");
}

QVariant DartsMultiScoreDataModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int DartsMultiScoreDataModel::numberOfAttemps() const
{
    return _attemps;
}

bool DartsMultiScoreDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

    auto scoresAtRow = _data.at(row);
    scoresAtRow.replace(column,value.toInt());
    _data.replace(row,scoresAtRow);

    auto scoreGlypWidth = stringWidth(QString::number(value.toInt()),
                                      scoreFontFamily(),
                                      scoreFontSize());
    if(scoreGlypWidth > columnWidthsAt(column))
        setColumnWidthAt(column,scoreGlypWidth);

    emit dataChanged(index,index,{role});
    return true;
}

bool DartsMultiScoreDataModel::insertRows(int row, int count, const QModelIndex &)
{
    auto firstRow = row <= rowCount(QModelIndex()) ? row : rowCount(QModelIndex()) - 1;
    auto lastRow  =  row <= rowCount(QModelIndex()) ? firstRow + count : 2*row + count - firstRow;
    auto c = row <= rowCount(QModelIndex()) ? count : count + (row - firstRow) - 1;

    beginInsertRows(QModelIndex(),firstRow,lastRow);

    for (int i = 0; i < c; ++i) {
        auto initializedDataRow = [this]
        {
            LinkedList<int> resultingList;
            auto count = columnCount(QModelIndex(QModelIndex()));
            for (int i = 0; i < count; ++i)
                resultingList << -1;
            return resultingList;
        }();
        _data.insert(row,initializedDataRow);
    }

    endInsertRows();

    _rows += c;

    emit dataChanged(createIndex(row,0),createIndex(lastRow,columnCount()));

    return true;
}

bool DartsMultiScoreDataModel::insertColumns(int column, int count, const QModelIndex &)
{
    auto firstColumn = column <= columnCount() ? column : columnCount() - 1;
    auto lastColumn  =  column <= columnCount() ? firstColumn + count : 2*column + count - firstColumn;
    auto c = column <= columnCount() ? count : count + (column - firstColumn) - 1;

    beginInsertColumns(QModelIndex(),firstColumn,lastColumn);

    for (int i = 0;i<_data.count();i++) {
        auto columnsData = _data.at(i);
        LinkedList<int> columnsDataIndice;
        for (int i = 0; i < c; ++i)
            columnsDataIndice << -1;
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

bool DartsMultiScoreDataModel::removeRows(int row, int count, const QModelIndex &)
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

bool DartsMultiScoreDataModel::removeColumns(int column, int count, const QModelIndex &)
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

void DartsMultiScoreDataModel::updateInitialCellValues()
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

bool DartsMultiScoreDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int DartsMultiScoreDataModel::indexOfLastDecoratedCell(const int &index,const int &orientation)
{
    if(orientation == Qt::Vertical)
    {
        auto row = index;
        if(row >= _data.count() || row < 0)
            return -1;
        auto scoresAtRow = _data.at(row);

        for (int col = 0; col < columnCount(QModelIndex()); ++col) {
            auto score = scoresAtRow.at(col);
            if(score == -1)
                return col - 1;
        }
        return columnCount() - 1;
    }
    else if(orientation == Qt::Horizontal)
    {
        for (int row = 0; row < rowCount(); ++row) {
            auto scoresAtRow = _data.at(row);
            auto score = scoresAtRow.at(index);
            if(score == -1)
                return row - 1;
        }
        return rowCount() - 1;
    }
    else
    {
        return -1;
    }
}

int DartsMultiScoreDataModel::rowCount(const int &column)
{
    for (int row = 0; row < _data.count(); ++row) {
        auto scoreAtRow = _data.at(row);
        auto score = scoreAtRow.at(column);
        auto scoreModelsCount = scoreAtRow.count();
        if(scoreModelsCount > column && score == -1)
            return row;
    }
    return rowCount();
}

bool DartsMultiScoreDataModel::isColumnEmpty(const int &col)
{
    if(col < 0 || col >= columnCount())
        throw std::out_of_range("Index out of range");
    for (auto scoresAtRow : qAsConst(_data)) {
        auto score = scoresAtRow.at(col);
        if(score != -1)
            return false;
    }
    return true;
}

bool DartsMultiScoreDataModel::isRowEmpty(const int &row)
{
    if(row < 0 || row >= rowCount())
        throw std::out_of_range("Index out of range");
    auto columnsData = _data.at(row);
    for (int i = 0; i < columnsData.count(); ++i) {
        auto score = columnsData.at(i);
        if(score != -1)
            return false;
    }
    return true;
}

int DartsMultiScoreDataModel::removeData(const QModelIndex &index)
{
    if(!index.isValid())
        return -1;
    auto row = index.row();
    auto column = index.column();
    auto columnData = _data.at(row);
    auto data = columnData.at(column);
    auto initialValue = -1;

    columnData.replace(column,initialValue);
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

int DartsMultiScoreDataModel::indexOfHeaderItem(const QString &data, const int &orientation)
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

int DartsMultiScoreDataModel::stringWidth(const QString &string, const QString &family, const int &pointSize) const
{
    auto fontMetric = QFontMetrics(QFont(family,pointSize));
    auto r = fontMetric.boundingRect(string).width();
    return r;
}

int DartsMultiScoreDataModel::headerFontSize() const
{
    return _headerFontSize;
}

void DartsMultiScoreDataModel::setHeaderFontSize(int headerFontSize)
{
    _headerFontSize = headerFontSize;
}

QStringList DartsMultiScoreDataModel::getHorizontalHeaderData() const
{
    return _horizontalHeaderData;
}

void DartsMultiScoreDataModel::setHorizontalHeaderData(const QList<QString> &horizontalHeaderData)
{
    _horizontalHeaderData = horizontalHeaderData;
}

QStringList DartsMultiScoreDataModel::getVerticalHeaderData() const
{
    return _verticalHeaderData;
}

void DartsMultiScoreDataModel::setVerticalHeaderData(const QList<QString> &verticalHeaderData)
{
    _verticalHeaderData = verticalHeaderData;
}

int DartsMultiScoreDataModel::appendMode() const
{
    return _appendMode;
}

void DartsMultiScoreDataModel::setAppendMode(int appendMode)
{
    _appendMode = appendMode;
}

QString DartsMultiScoreDataModel::pointFontFamily() const
{
    return _pointFontFamily;
}

void DartsMultiScoreDataModel::setPointFontFamily(const QString &pointFontFamily)
{
    _pointFontFamily = pointFontFamily;
}

QString DartsMultiScoreDataModel::scoreFontFamily() const
{
    return _scoreFontFamily;
}

void DartsMultiScoreDataModel::setScoreFontFamily(const QString &scoreFontFamily)
{
    _scoreFontFamily = scoreFontFamily;
}

int DartsMultiScoreDataModel::pointFontSize() const
{
    return _pointFontSize;
}

void DartsMultiScoreDataModel::setPointFontSize(int pointFontSize)
{
    _pointFontSize = pointFontSize;
}

int DartsMultiScoreDataModel::scoreFontSize() const
{
    return _scoreFontSize;
}

void DartsMultiScoreDataModel::setScoreFontSize(int scoreFontSize)
{
    _scoreFontSize = scoreFontSize;
}

int DartsMultiScoreDataModel::initialValue() const
{
    return _initialValue;
}

void DartsMultiScoreDataModel::setInitialValue(int initialValue)
{
    _initialValue = initialValue;
    emit initialValueChanged();
}

int DartsMultiScoreDataModel::minimumRowCount() const
{
    return _minimumRowCount;
}

void DartsMultiScoreDataModel::setMinimumRowCount(int minimumRowCount)
{
    if(appendMode() == AppendDataMode::SingleAppend)
        return;
    _minimumRowCount = minimumRowCount;
    auto rowCount = this->rowCount();
    if(minimumRowCount > rowCount)
        setRowCount(minimumRowCount);
}

int DartsMultiScoreDataModel::minimumColumnCount() const
{
    return _minimumColumnCount;
}

void DartsMultiScoreDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    if(appendMode() == AppendDataMode::SingleAppend)
        return;
    _minimumColumnCount = minimumColumnCount;
    auto colCount = columnCount();
    if(minimumColumnCount > colCount)
        setColumnCount(minimumColumnCount);
    emit minimumColumnCountChanged();
}

int DartsMultiScoreDataModel::headerOrientation() const
{
    return _headerOrientation;
}

void DartsMultiScoreDataModel::setHeaderOrientation(int headerOrientation)
{
    _headerOrientation = headerOrientation;
}

int DartsMultiScoreDataModel::preferedHeaderItemWidth() const
{
    auto preferedWidth = columnWidthsAt(0);
    return preferedWidth;
}

void DartsMultiScoreDataModel::setNumberOfAttemps(const int &count)
{
    _attemps = count;
    emit dataChanged(QModelIndex(),QModelIndex());
}

void DartsMultiScoreDataModel::setColumnCount(const int &count)
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

void DartsMultiScoreDataModel::setRowCount(const int &count)
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

double DartsMultiScoreDataModel::scale() const
{
    return _scale;
}

void DartsMultiScoreDataModel::setScale(double scale)
{
    _scale = scale;
}

int DartsMultiScoreDataModel::horizontalHeaderFillMode() const
{
    return _horizontalFillMode;
}

int DartsMultiScoreDataModel::verticalHeaderFillMode() const
{
    return _verticalFillMode;
}

void DartsMultiScoreDataModel::setHorizontalHeaderFillMode(const int &fillMode)
{
    _horizontalFillMode = fillMode;
    emit fillModeChanged();
}

void DartsMultiScoreDataModel::setVerticalHeaderFillMode(const int &fillMode)
{
    _verticalFillMode = fillMode;
    emit fillModeChanged();
}
