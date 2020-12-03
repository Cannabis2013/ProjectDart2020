#include "firsttopostdatamodel.h"

FirstToPostDataModel::FirstToPostDataModel()
{
    connect(this,&FirstToPostDataModel::initialValueChanged,this,&FirstToPostDataModel::updateInitialCellValues);
}

QVariant FirstToPostDataModel::getData(const int &row, const int &column, const int &mode)
{
    if(row >= rowCount() || column >= columnCount())
        return -1;
    auto columnsData = _data.at(row);
    auto columnData = columnsData.at(column);
    auto result = mode == 0x1 ? columnData.first : columnData.second;
    if(result == -1)
        return "-";
    else
        return result;
}

int FirstToPostDataModel::editData(const int &row, const int &column, const int &point, const int &score)
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

bool FirstToPostDataModel::insertData(const QString &playerName,
                                         const int &point,
                                         const int &score)
{
    if(headerOrientation() == Qt::Horizontal)
    {
        if(appendMode() == AppendDataMode::SingleAppend)
            return setPlayerData(playerName,point,score,headerOrientation());
        else
            return appendPlayerData(playerName,point,score,headerOrientation());
    }
    else if(headerOrientation() == Qt::Vertical)
    {
        if(appendMode() == AppendDataMode::SingleAppend)
            return setPlayerData(playerName,point,score,headerOrientation());
        else
            return appendPlayerData(playerName,point,score,headerOrientation());
    }

    return false;
}

bool FirstToPostDataModel::setPlayerData(const QString &playerName, const int &point, const int &score, const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    auto index = indexOfHeaderItem(playerName,orientation);
    auto pair = scoreModel(point,score);
    if(orientation == Qt::Horizontal)
    {
        auto row = 0;
        auto modelIndex = this->createIndex(row,index);

        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,QVariant::fromValue<scoreModel>(pair),Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    else if(orientation == Qt::Vertical)
    {
        auto column = 0;
        auto modelIndex = this->createIndex(index,column);
        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,QVariant::fromValue<scoreModel>(pair),Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    return true;
}

bool FirstToPostDataModel::appendPlayerData(const QString &playerName,
                                const int &point,
                                const int &score,
                                const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    auto index = indexOfHeaderItem(playerName,orientation);
    auto pair = scoreModel(point,score);
    if(orientation == Qt::Horizontal)
    {
        auto row = index < columnCount() ? rowCount(index) : 0;
        auto modelIndex = this->createIndex(row,index);

        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,QVariant::fromValue<scoreModel>(pair),Qt::DisplayRole);
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
            setData(modelIndex,QVariant::fromValue<scoreModel>(pair),Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    return true;
}

bool FirstToPostDataModel::removeLastItem(const QString &playerName, const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    if(orientation == Qt::Horizontal)
    {
        auto column = indexOfHeaderItem(playerName,orientation);
        auto row = indexOfLastDecoratedCell(column,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index) != scoreModel(-1,-1);
        return result;
    }
    else
    {
        auto row = indexOfHeaderItem(playerName,orientation);
        auto column = indexOfLastDecoratedCell(row,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index) != scoreModel(-1,-1);
        return result;
    }
}

void FirstToPostDataModel::appendHeaderItem(const QVariant &data, const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    auto glyphLength = stringWidth(data.toString(),scoreFontFamily(),scoreFontSize()).width();
    if(orientation == Qt::Horizontal){
        if(_horizontalHeaderData.count() >= columnCount())
            insertColumns(_horizontalHeaderData.count(),1,QModelIndex());
        else
            emit dataChanged(QModelIndex(),QModelIndex());
        if(glyphLength > currentHorizontalHeaderItemWidth())
            setCurrentHorizontalHeaderItemWidth(glyphLength);
        _horizontalHeaderData.append(data.toString());
    }
    else{
        if(_verticalHeaderData.count() >= rowCount())
            insertRows(_verticalHeaderData.count(),1,QModelIndex());
        else
            emit dataChanged(QModelIndex(),QModelIndex());
        _verticalHeaderData.append(data.toString());
        if(glyphLength > currentVerticalHeaderItemWidth())
            setCurrentVerticalHeaderItemWidth(glyphLength);
    }
}

void FirstToPostDataModel::clearData()
{
    _data.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    _columns = 0;
    _rows = 0;

    _horizontalHeaderData.clear();
    _verticalHeaderData.clear();

    emit dataChanged(createIndex(0,0),bottomRight);
}

QString FirstToPostDataModel::getHeaderData(const int &index, const int &headerOrientation) const
{
    auto orientation = headerOrientation != -1 ? headerOrientation :
                                                 this->headerOrientation();
    auto value = headerData(index,static_cast<Qt::Orientation>(orientation),Qt::DisplayRole).toString();
    return value;
}

int FirstToPostDataModel::headerItemCount(const int &headerOrientation) const
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

int FirstToPostDataModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int FirstToPostDataModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double FirstToPostDataModel::columnWidthAt(const int &column) const
{
    int headerGlyphLength = defaultCellWidth;
    QString headerDataAtColumn = "";

    if(horizontalHeaderFillMode() == HeaderFillMode::FixedStrings)
    {
        if(column < _horizontalHeaderData.count())
            headerDataAtColumn = _horizontalHeaderData.at(column);
        headerGlyphLength = stringWidth(headerDataAtColumn,
                                        scoreFontFamily(),
                                        scoreFontSize()).width();
    }


    auto greatestColumnGlyphLength = _columnWidths.at(column);
    auto greatestGlyphLength = headerGlyphLength > greatestColumnGlyphLength ? headerGlyphLength :
                                                                               greatestColumnGlyphLength;
    return greatestGlyphLength * scale();
}

double FirstToPostDataModel::rowHeightAt(const int &row) const
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
            return defaultCellHeight;
    }
    else
        headerString = _verticalHeaderData.at(row);

    auto resultingGlyphLenght = scoreFontMetric.boundingRect(headerString).height();
    auto count = columnCount();
    for (int c = 0; c < count; ++c) {
        auto columnsData = _data.at(row);
        if(columnsData.count() != columnCount())
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

    if(resultingGlyphLenght < defaultCellHeight)
        resultingGlyphLenght = defaultCellHeight;

    return resultingGlyphLenght;
}

int FirstToPostDataModel::horizontalHeaderCount() const
{
    return _horizontalHeaderData.count();
}

int FirstToPostDataModel::verticalHeaderCount() const
{
    return _verticalHeaderData.count();
}

int FirstToPostDataModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int FirstToPostDataModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

void FirstToPostDataModel::setColumnWidthAt(const int &column, const double &w)
{
    _columnWidths.replace(column,w);
}

QVariant FirstToPostDataModel::data(const QModelIndex &index, int role) const
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
    auto point = pair.first;
    auto score = pair.second;
    auto data = QString::number(point) + " " + QString::number(score);
    return score >= 0 ?
                QVariant(data) :
                QVariant("-");
}

QVariant FirstToPostDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    auto roundIndex = (section - 1)/_numberOfThrows + 1;

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

int FirstToPostDataModel::numberOfThrows() const
{
    return _numberOfThrows;
}

bool FirstToPostDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto row = index.row();
    auto column = index.column();

    if(row < 0 || column < 0)
        return false;

    if(row >= rowCount())
    {
        auto deltaR = numberOfThrows();
        insertRows(row,deltaR,QModelIndex());
    }

    if(column >= columnCount())
    {
        auto deltaC = numberOfThrows();
        insertColumns(column,deltaC,QModelIndex());
    }

    auto pairs = _data.at(row);

    auto newPair = value.value<scoreModel>();

    pairs.replace(column,newPair);

    _data.replace(row,pairs);

    auto pointGlypWidth = stringWidth(QString::number(newPair.first),
                                      pointFontFamily(),
                                      pointFontSize()).width();
    auto scoreGlypWidth = stringWidth(QString::number(newPair.second),
                                      scoreFontFamily(),
                                      scoreFontSize()).width();
    int totalGlyphWidth = pointGlypWidth + scoreGlypWidth;
    if(totalGlyphWidth > _columnWidths.at(column))
        setColumnWidthAt(column,totalGlyphWidth);

    emit dataChanged(index,index,{role});

    return true;
}

bool FirstToPostDataModel::insertRows(int row, int count, const QModelIndex &)
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

bool FirstToPostDataModel::insertColumns(int column, int count, const QModelIndex &)
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
        newColumnWidths << defaultCellWidth;

    for (int i = 0; i < newColumnWidths.count(); ++i) {
        auto columnWidth = newColumnWidths.at(i);
        _columnWidths.insert(column,columnWidth);
    }

    endInsertColumns();

    _columns += c;

    emit dataChanged(createIndex(0,firstColumn),
                     createIndex(headerItemCount(0x2),lastColumn));
    cout << "Insert columns done" << endl;
    return true;
}

bool FirstToPostDataModel::removeRows(int row, int count, const QModelIndex &)
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

bool FirstToPostDataModel::removeColumns(int column, int count, const QModelIndex &)
{
    // Check if input satisfies model constraints
    if(column < 0 || column >= columnCount())
        return false;

    // Begin remove columns
    beginRemoveColumns(QModelIndex(),column,column + count);

    for (auto &row : _data) {
        for (int i = column; i < column + count; ++i)
            row.removeAt(i);
    }

    endRemoveColumns();

    _columns -= count;

    emit dataChanged(createIndex(0,column),createIndex(headerItemCount(0x2),column + count));

    return true;
}

void FirstToPostDataModel::updateInitialCellValues()
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

bool FirstToPostDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int FirstToPostDataModel::indexOfLastDecoratedCell(const int &index,const int &orientation)
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

int FirstToPostDataModel::rowCount(const int &column)
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

bool FirstToPostDataModel::isColumnEmpty(const int &col)
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

bool FirstToPostDataModel::isRowEmpty(const int &row)
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

QPair<int, int> FirstToPostDataModel::removeData(const QModelIndex &index)
{
    if(!index.isValid())
        return scoreModel(-1,-1);
    auto row = index.row();
    auto column = index.column();
    auto pairsRow = _data.at(row);
    auto pair = pairsRow.at(column);
    auto initialPair = scoreModel(-1,-1);

    pairsRow.replace(column,initialPair);
    _data.replace(row,pairsRow);
    if(headerOrientation() == Qt::Vertical)
    {
        if(isColumnEmpty(column) && column > minimumColumnCount())
            removeColumns(column,1,QModelIndex());
    }
    else
    {
        if(isRowEmpty(row) && row > minimumRowCount())
            removeColumns(column,1,QModelIndex());
    }

    emit dataChanged(createIndex(row,column),createIndex(row,column));
    return pair;
}

int FirstToPostDataModel::indexOfHeaderItem(const QString &data, const int &orientation)
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

QRect FirstToPostDataModel::stringWidth(const QString &string, const QString &family, const int &pointSize) const
{
    auto fontMetric = QFontMetrics(QFont(family,pointSize));
    auto r = fontMetric.boundingRect(string);
    return r;
}

QStringList FirstToPostDataModel::getHorizontalHeaderData() const
{
    return _horizontalHeaderData;
}

void FirstToPostDataModel::setHorizontalHeaderData(const QList<QString> &horizontalHeaderData)
{
    _horizontalHeaderData = horizontalHeaderData;
}

QStringList FirstToPostDataModel::getVerticalHeaderData() const
{
    return _verticalHeaderData;
}

void FirstToPostDataModel::setVerticalHeaderData(const QList<QString> &verticalHeaderData)
{
    _verticalHeaderData = verticalHeaderData;
}

int FirstToPostDataModel::appendMode() const
{
    return _appendMode;
}

void FirstToPostDataModel::setAppendMode(int appendMode)
{
    _appendMode = appendMode;
}

void FirstToPostDataModel::setCurrentVerticalHeaderItemWidth(int currentVerticalHeaderItemWidth)
{
    _currentVerticalHeaderItemWidth = currentVerticalHeaderItemWidth;
}

void FirstToPostDataModel::setCurrentHorizontalHeaderItemWidth(int currentHorizontalHeaderItemWidth)
{
    _currentHorizontalHeaderItemWidth = currentHorizontalHeaderItemWidth;
}

int FirstToPostDataModel::currentHorizontalHeaderItemWidth() const
{
    return _currentHorizontalHeaderItemWidth;
}

int FirstToPostDataModel::currentVerticalHeaderItemWidth() const
{
    return _currentVerticalHeaderItemWidth;
}


QString FirstToPostDataModel::pointFontFamily() const
{
    return _pointFontFamily;
}

void FirstToPostDataModel::setPointFontFamily(const QString &pointFontFamily)
{
    _pointFontFamily = pointFontFamily;
}

QString FirstToPostDataModel::scoreFontFamily() const
{
    return _scoreFontFamily;
}

void FirstToPostDataModel::setScoreFontFamily(const QString &scoreFontFamily)
{
    _scoreFontFamily = scoreFontFamily;
}

int FirstToPostDataModel::pointFontSize() const
{
    return _pointFontSize;
}

void FirstToPostDataModel::setPointFontSize(int pointFontSize)
{
    _pointFontSize = pointFontSize;
}

int FirstToPostDataModel::scoreFontSize() const
{
    return _scoreFontSize;
}

void FirstToPostDataModel::setScoreFontSize(int scoreFontSize)
{
    _scoreFontSize = scoreFontSize;
}

int FirstToPostDataModel::initialValue() const
{
    return _initialValue;
}

void FirstToPostDataModel::setInitialValue(int initialValue)
{
    _initialValue = initialValue;
    emit initialValueChanged();
}

int FirstToPostDataModel::minimumRowCount() const
{
    return _minimumRowCount;
}

void FirstToPostDataModel::setMinimumRowCount(int minimumRowCount)
{
    if(appendMode() == AppendDataMode::SingleAppend)
        return;
    _minimumRowCount = minimumRowCount;
    auto rowCount = this->rowCount();
    if(minimumRowCount > rowCount)
        setRowCount(minimumRowCount);
}

int FirstToPostDataModel::minimumColumnCount() const
{
    return _minimumColumnCount;
}

void FirstToPostDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    cout << "setMinimumColumnCount reached" << endl;
    if(appendMode() == AppendDataMode::SingleAppend)
        return;
    _minimumColumnCount = minimumColumnCount;
    auto colCount = columnCount();
    if(minimumColumnCount > colCount)
        setColumnCount(minimumColumnCount);
    emit minimumColumnCountChanged();
}

int FirstToPostDataModel::headerOrientation() const
{
    return _headerOrientation;
}

void FirstToPostDataModel::setHeaderOrientation(int headerOrientation)
{
    _headerOrientation = headerOrientation;
}

int FirstToPostDataModel::preferedHeaderItemWidth(const int &orientation) const
{
    auto result = defaultCellWidth;
    if(orientation == Qt::Vertical)
    {
        if(verticalHeaderFillMode() == HeaderFillMode::DynamicNumerics)
            result = rowCount() / _numberOfThrows;
        else if(verticalHeaderFillMode() == HeaderFillMode::FixedStrings)
            result = currentVerticalHeaderItemWidth();
    }
    if(result < defaultCellWidth)
        result = defaultCellWidth;
    return result;
}

void FirstToPostDataModel::setNumberOfThrows(const int &count)
{
    _numberOfThrows = count;
}

void FirstToPostDataModel::setColumnCount(const int &count)
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

void FirstToPostDataModel::setRowCount(const int &count)
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

double FirstToPostDataModel::scale() const
{
    return _scale;
}

void FirstToPostDataModel::setScale(double scale)
{
    _scale = scale;
}

int FirstToPostDataModel::horizontalHeaderFillMode() const
{
    return _horizontalFillMode;
}

int FirstToPostDataModel::verticalHeaderFillMode() const
{
    return _verticalFillMode;
}

void FirstToPostDataModel::setHorizontalHeaderFillMode(const int &fillMode)
{
    _horizontalFillMode = fillMode;
    emit fillModeChanged();
}

void FirstToPostDataModel::setVerticalHeaderFillMode(const int &fillMode)
{
    _verticalFillMode = fillMode;
    emit fillModeChanged();
}
