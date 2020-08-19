#include "scoredatamodel.h"

ScoreDataModel::ScoreDataModel()
{
    connect(this,&ScoreDataModel::initialValueChanged,this,&ScoreDataModel::updateInitialCellValues);
}

QVariant ScoreDataModel::getData(const int &row, const int &column, const int &mode)
{
    if(row >= rowCount() || column >= columnCount())
        return -1;
    auto pairsRow = _pairs.at(row);
    auto pair = pairsRow.at(column);
    auto result = mode == 0x1 ? pair.first : pair.second;
    if(result == -1)
        return "-";
    else
        return result;
}

int ScoreDataModel::editData(const int &row, const int &column, const int &point, const int &score)
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

bool ScoreDataModel::appendData(const QString &playerName,
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
        auto rowCount = _pairs.count();
        auto column = index < rowCount ? indexOfLastDecoratedCell(index,orientation) + 1 : 0;
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

bool ScoreDataModel::removeLastItem(const QString &playerName, const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    if(orientation == Qt::Horizontal)
    {
        auto column = indexOfHeaderItem(playerName,orientation);
        auto row = indexOfLastDecoratedCell(column,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index) == scoreModel(-1,-1);
        return result;
    }
    else
    {
        auto row = indexOfHeaderItem(playerName,orientation);
        auto column = indexOfLastDecoratedCell(row,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index) == scoreModel(-1,-1);
        return result;
    }
}

void ScoreDataModel::appendHeaderItem(const QVariant &data, const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    if(orientation == Qt::Horizontal){
        if(_horizontalHeaderData.count() >= columnCount())
            insertColumns(_horizontalHeaderData.count(),1,QModelIndex());
        else
            emit dataChanged(QModelIndex(),QModelIndex());
        _horizontalHeaderData.append(data.toString());
    }
    else{
        if(_verticalHeaderData.count() >= rowCount())
            insertRows(_verticalHeaderData.count(),1,QModelIndex());
        else
            emit dataChanged(QModelIndex(),QModelIndex());
        _verticalHeaderData.append(data.toString());
    }
}

void ScoreDataModel::clearData()
{
    _pairs.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    _columns = 0;
    _rows = 0;
    _horizontalHeaderData.clear();
    _verticalHeaderData.clear();
    emit dataChanged(createIndex(0,0),bottomRight);
}

QString ScoreDataModel::getHeaderData(const int &index, const int &headerOrientation) const
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    auto value =  headerData(index,static_cast<Qt::Orientation>(orientation),Qt::DisplayRole).toString();
    return value;
}

int ScoreDataModel::headerItemCount(const int &headerOrientation) const
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    if(orientation == Qt::Horizontal)
        return _horizontalHeaderData.count();
    else
        return _verticalHeaderData.count();
}

int ScoreDataModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int ScoreDataModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double ScoreDataModel::columnWidthAt(const int &column) const
{
    if(column >= columnCount() || _pairs.count() <= 0)
        return -1;

    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),scoreFontSize()));
    auto pointFontmetric = QFontMetrics(QFont(pointFontFamily(),pointFontSize()));

    QString headerString;

    if(_horizontalHeaderData.count() <= column){
        if(horizontalHeaderFillMode() == HeaderFillMode::IncrementingNumericFillMode)
            headerString = QString::number(column + 1);
    }
    else
    {
        headerString = _horizontalHeaderData.at(column);
    }

    auto resultingGlyphLenght = scoreFontMetric.boundingRect(headerString).width();

    for (int r = 0; r < rowCount(); ++r) {
        auto row = _pairs.at(r);
        if(row.count() != columnCount())
            return 0;
        auto pair = row.at(column);
        auto point = pair.first;
        auto score = pair.second;
        auto pointString = QString::number(point);
        auto scoreString = QString::number(score);
        auto scoreGlyphWidth = scoreFontMetric.boundingRect(scoreString).width();
        auto pointGlyphWidth = pointFontmetric.boundingRect(pointString).width();
        auto totalGlypWidth = scoreGlyphWidth + pointGlyphWidth;
        resultingGlyphLenght = totalGlypWidth > resultingGlyphLenght ? totalGlypWidth :
                                                                    resultingGlyphLenght;
    }

    if(resultingGlyphLenght < 25)
        return defaultCellWidth *scale();

    return resultingGlyphLenght * scale();
}

double ScoreDataModel::rowHeightAt(const int &row) const
{
    if(_pairs.count() <= 0)
        return 0;

    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),scoreFontSize()));
    auto pointFontmetric = QFontMetrics(QFont(pointFontFamily(),pointFontSize()));

    QString headerString;

    if(_verticalHeaderData.count() <= row)
    {
        if(verticalHeaderFillMode() == HeaderFillMode::IncrementingNumericFillMode)
            headerString = QString::number(row + 1);
        else
            return defaultCellHeight;
    }
    else
        headerString = _verticalHeaderData.at(row);

    auto resultingGlyphLenght = scoreFontMetric.boundingRect(headerString).height();
    auto count = columnCount();
    for (int c = 0; c < count; ++c) {
        auto pairs = _pairs.at(row);
        if(pairs.count() != columnCount())
            return 0;
        auto pair = pairs.at(c);
        auto point = pair.first;
        auto score = pair.second;
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

int ScoreDataModel::horizontalHeaderCount() const
{
    return _horizontalHeaderData.count();
}

int ScoreDataModel::verticalHeaderCount() const
{
    return _verticalHeaderData.count();
}

int ScoreDataModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int ScoreDataModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

QVariant ScoreDataModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || _pairs.count() <= 0)
        return QVariant();
    auto row = index.row();
    auto column = index.column();
    auto pairs = _pairs.at(row);
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

QVariant ScoreDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    auto horizontalHeaderCount = _horizontalHeaderData.count();
    int roundIndex = (section - 1)/_numberOfThrows;

    switch (orientation) {
        case Qt::Horizontal : return section == 0 ? 0 : horizontalHeaderFillMode() == HeaderFillMode::IncrementingNumericFillMode ?
                        QVariant(roundIndex + 1) : section < horizontalHeaderCount ?
                            _horizontalHeaderData.at(section) : QVariant();
        case Qt::Vertical : return section < _verticalHeaderData.count() ?
                        _verticalHeaderData.at(section) :  verticalHeaderFillMode() == HeaderFillMode::IncrementingNumericFillMode ?
                            QVariant(roundIndex + 1) : QVariant();
        default: return QVariant();
    }
}

int ScoreDataModel::numberOfThrows() const
{
    return _numberOfThrows;
}

bool ScoreDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto row = index.row();
    auto column = index.column();

    if(row < 0 || column < 0)
        return false;

    if(row >= rowCount())
    {
        auto deltaR = row -(rowCount() - 1);
        insertRows(row,deltaR,QModelIndex());
    }

    if(column >= columnCount())
    {
        auto deltaC = column - (columnCount() - 1);
        insertColumns(column,deltaC,QModelIndex());
    }

    auto pairs = _pairs.at(row);

    auto newPair = value.value<scoreModel>();

    pairs.replace(column,newPair);

    _pairs.replace(row,pairs);

    emit dataChanged(index,index,{role});

    return true;
}

bool ScoreDataModel::insertRows(int row, int count, const QModelIndex &)
{
    auto firstRow = row <= rowCount(QModelIndex()) ? row : rowCount(QModelIndex()) - 1;
    auto lastRow  =  row <= rowCount(QModelIndex()) ? firstRow + count : 2*row + count - firstRow;
    auto c = row <= rowCount(QModelIndex()) ? count : count + (row - firstRow) - 1;

    beginInsertRows(QModelIndex(),firstRow,lastRow);

    for (int i = 0; i < c; ++i) {
        auto initializedDataRow = [this]
        {
            QList<scoreModel> resultingList;
            auto count = columnCount(QModelIndex(QModelIndex()));
            for (int i = 0; i < count; ++i)
                resultingList << scoreModel(-1,-1);
            return resultingList;
        }();
        _pairs.insert(row,initializedDataRow);
    }

    endInsertRows();

    _rows += c;

    emit dataChanged(createIndex(row,0),createIndex(lastRow,columnCount()));

    return true;
}

bool ScoreDataModel::insertColumns(int column, int count, const QModelIndex &)
{
    auto firstColumn = column <= columnCount(QModelIndex()) ? column : columnCount(QModelIndex()) - 1;
    auto lastColumn  =  column <= columnCount(QModelIndex()) ? firstColumn + count : 2*column + count - firstColumn;
    auto c = column <= columnCount(QModelIndex()) ? count : count + (column - firstColumn) - 1;

    beginInsertColumns(QModelIndex(),firstColumn,lastColumn);

    for (int i = 0;i<_pairs.count();i++) {
        auto pairsRow = _pairs.at(i);
        QList<scoreModel> initialDataValues = [c]
        {
            QList<scoreModel> resultingList;

            for (int i = 0; i < c; ++i)
                resultingList << scoreModel(-1,-1);

            return resultingList;
        }();
        for (int j = 0; j < initialDataValues.count(); ++j) {
            auto dataValue = initialDataValues.at(j);
            pairsRow.insert(column,dataValue);
        }
        _pairs.replace(i,pairsRow);
    }

    endInsertColumns();

    _columns += c;

    emit dataChanged(createIndex(0,firstColumn),createIndex(headerItemCount(0x2),lastColumn));

    return true;
}

bool ScoreDataModel::removeRows(int row, int count, const QModelIndex &)
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
        _pairs.removeAt(i);
        // Remove corresponding header rows
        _verticalHeaderData.removeAt(i);
    }

    endRemoveRows();

    _rows -= count;

    // Notify model and surrounding state that data has changed
    emit dataChanged(topLeftIndex,bottomRightIndex,{Qt::DisplayRole});

    return true;
}

bool ScoreDataModel::removeColumns(int column, int count, const QModelIndex &)
{
    // Check if input satisfies model constraints
    if(column < 0 || column >= columnCount())
        return false;

    // Begin remove columns
    beginRemoveColumns(QModelIndex(),column,column + count);

    for (auto &row : _pairs) {
        for (int i = column; i < column + count; ++i)
            row.removeAt(i);
    }

    endRemoveColumns();

    _columns -= count;

    emit dataChanged(createIndex(0,column),createIndex(headerItemCount(0x2),column + count));

    return true;
}

void ScoreDataModel::updateInitialCellValues()
{

    if(_pairs.count() < 1)
        return;
    auto orientation = _headerOrientation;
    auto initialValue = this->initialValue();
    if(orientation == Qt::Horizontal)
    {
        auto firstColumn = _pairs.at(0);
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

bool ScoreDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int ScoreDataModel::indexOfLastDecoratedCell(const int &index,const int &orientation)
{
    if(orientation == Qt::Vertical)
    {
        auto pairs = _pairs.at(index);

        for (int col = 0; col < columnCount(QModelIndex()); ++col) {
            auto pair = pairs.at(col);
            auto score = pair.first;

            if(score == -1)
                return col - 1;
        }

        return columnCount() - 1;
    }
    else if(orientation == Qt::Horizontal)
    {
        for (int row = 0; row < rowCount(); ++row) {
            auto pairs = _pairs.at(row);
            auto pair = pairs.at(index);
            auto score = pair.first;
            if(score == -1)
                return row -1;
        }
        return rowCount() - 1;
    }
    else
        return -1;
}

int ScoreDataModel::rowCount(const int &column)
{
    for (int row = 0; row < _pairs.count(); ++row) {
        auto pairsRow = _pairs.at(row);
        auto pair = pairsRow.at(column);
        auto point = pair.first;
        if(pairsRow.count() < column && point == -1)
            return row;
    }
    return rowCount();
}

bool ScoreDataModel::isColumnEmpty(const int &col)
{
    if(col < 0 || col >= columnCount())
        throw std::out_of_range("Index out of range");

    for (auto pairsRow : _pairs) {
        auto pair = pairsRow.at(col);
        auto point = pair.first;
        if(point != -1)
            return false;
    }
    return true;
}

bool ScoreDataModel::isRowEmpty(const int &row)
{
    if(row < 0 || row >= rowCount())
        throw std::out_of_range("Index out of range");
    auto pairsRow = _pairs.at(row);
    for (auto pair : pairsRow) {
        auto point = pair.first;
        if(point != -1)
            return false;
    }
    return true;
}

QPair<int, int> ScoreDataModel::removeData(const QModelIndex &index)
{
    if(!index.isValid())
        return scoreModel(-1,-1);
    auto row = index.row();
    auto column = index.column();
    auto pairsRow = _pairs.at(row);
    auto pair = pairsRow.at(column);
    auto initialPair = scoreModel(-1,-1);

    pairsRow.replace(column,initialPair);
    _pairs.replace(row,pairsRow);
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

int ScoreDataModel::indexOfHeaderItem(const QString &data, const int &orientation)
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

QString ScoreDataModel::pointFontFamily() const
{
    return _pointFontFamily;
}

void ScoreDataModel::setPointFontFamily(const QString &pointFontFamily)
{
    _pointFontFamily = pointFontFamily;
}

QString ScoreDataModel::scoreFontFamily() const
{
    return _scoreFontFamily;
}

void ScoreDataModel::setScoreFontFamily(const QString &scoreFontFamily)
{
    _scoreFontFamily = scoreFontFamily;
}

int ScoreDataModel::pointFontSize() const
{
    return _pointFontSize;
}

void ScoreDataModel::setPointFontSize(int pointFontSize)
{
    _pointFontSize = pointFontSize;
}

int ScoreDataModel::scoreFontSize() const
{
    return _scoreFontSize;
}

void ScoreDataModel::setScoreFontSize(int scoreFontSize)
{
    _scoreFontSize = scoreFontSize;
}

int ScoreDataModel::initialValue() const
{
    return _initialValue;
}

void ScoreDataModel::setInitialValue(int initialValue)
{
    _initialValue = initialValue;
    emit initialValueChanged();
}

int ScoreDataModel::minimumRowCount() const
{
    return _minimumRowCount;
}

void ScoreDataModel::setMinimumRowCount(int minimumRowCount)
{
    _minimumRowCount = minimumRowCount;
    emit minimumRowCountChanged();
}

int ScoreDataModel::minimumColumnCount() const
{
    return _minimumColumnCount;
}

void ScoreDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    _minimumColumnCount = minimumColumnCount;
    auto colCount = columnCount();
    if(minimumColumnCount > colCount)
        setColumnCount(minimumColumnCount);
    emit minimumColumnCountChanged();
}

int ScoreDataModel::headerOrientation() const
{
    return _headerOrientation;
}

void ScoreDataModel::setHeaderOrientation(int headerOrientation)
{
    _headerOrientation = headerOrientation;
}

int ScoreDataModel::preferedCellWidth(const QString &fontFamily, const int &pointSize) const
{
    auto preferedWidth = -1;
    for (auto txt : _verticalHeaderData) {
        QFontMetrics metrics(QFont(fontFamily,pointSize));

        auto glypLenght = metrics.boundingRect(txt).width();

        preferedWidth = glypLenght > preferedWidth ? glypLenght : preferedWidth;
    }

    return preferedWidth;
}

void ScoreDataModel::setNumberOfThrows(const int &count)
{
    _numberOfThrows = count;
}

void ScoreDataModel::setColumnCount(const int &count)
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

double ScoreDataModel::scale() const
{
    return _scale;
}

void ScoreDataModel::setScale(double scale)
{
    _scale = scale;
}

int ScoreDataModel::horizontalHeaderFillMode() const
{
    return _horizontalFillMode;
}

int ScoreDataModel::verticalHeaderFillMode() const
{
    return _verticalFillMode;
}

void ScoreDataModel::setHorizontalHeaderFillMode(const int &fillMode)
{
    _horizontalFillMode = fillMode;
    emit fillModeChanged();
}

void ScoreDataModel::setVerticalHeaderFillMode(const int &fillMode)
{
    _verticalFillMode = fillMode;
    emit fillModeChanged();
}
