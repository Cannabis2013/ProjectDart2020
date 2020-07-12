#include "scoredatamodel.h"

ScoreDataModel::ScoreDataModel()
{
    connect(this,&ScoreDataModel::initialValueChanged,this,&ScoreDataModel::updateInitialCellValues);
}

int ScoreDataModel::editData(const int &row, const int &column, const int &data)
{
    if(row < 0 || row >= rowCount())
        return -1;
    else if(column < 0 || column >= columnCount())
        return -1;
    auto index = createIndex(row,column);
    if(!isCellDecorated(index))
        return -1;
    auto oldData = this->data(index,Qt::DisplayRole);
    if(!setData(index,data,Qt::DisplayRole))
        return -1;
    return oldData.toInt();
}

bool ScoreDataModel::appendData(const QString &playerName, const int &data, const int &headerOrientation)
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
            setData(modelIndex,QVariant(data),Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    else if(orientation == Qt::Vertical)
    {
        auto rowCount = _cellData.count();
        auto column = index < rowCount ? indexOfLastDecoratedCell(index,orientation) + 1 : 0;
        auto modelIndex = this->createIndex(index,column);
        if(!modelIndex.isValid())
            return false;
        try {
            setData(modelIndex,QVariant(data),Qt::DisplayRole);
        } catch (std::out_of_range *e) {
            printf("%s\n",e->what());
            return false;
        }
    }
    return true;
}

int ScoreDataModel::takeDate(const QString &playerName, const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    if(orientation == Qt::Horizontal)
    {
        auto column = indexOfHeaderItem(playerName,orientation);
        auto row = indexOfLastDecoratedCell(column,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index);
        return result;
    }
    else
    {
        auto row = indexOfHeaderItem(playerName,orientation);
        auto column = indexOfLastDecoratedCell(row,orientation);
        auto index = createIndex(row,column);
        auto result = removeData(index);
        return result;
    }

}

void ScoreDataModel::appendHeaderItem(const QVariant &data, const int &headerOrientation)
{
    auto orientation = headerOrientation != -1 ? headerOrientation : this->headerOrientation();
    if(orientation == Qt::Horizontal){
        if(_horizontalHeaderData.count() >= columnCount())
            insertColumns(_horizontalHeaderData.count(),1,QModelIndex());
        _horizontalHeaderData.append(data.toString());
    }
    else{
        if(_verticalHeaderData.count() >= rowCount())
            insertRows(_verticalHeaderData.count(),1,QModelIndex());
        _verticalHeaderData.append(data.toString());
    }

    //emit dataChanged(QModelIndex(),QModelIndex());
}

void ScoreDataModel::clearData()
{
    _cellData.clear();
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

double ScoreDataModel::columnWidthAt(const int &column, const QString &fontFamily, const int &pointSize) const
{
    if(column >= columnCount() || _cellData.count() <= 0)
        return -1;

    auto font = QFont(fontFamily,pointSize);

    QFontMetrics fontMetric(font);

    QString string;

    if(_horizontalHeaderData.count() <= column){

        if(fillMode() == HeaderFillMode::IncrementingIntegerFill)
            string = QString::number(column + 1);
    }
    else
        string = _horizontalHeaderData.at(column);

    auto resultingGlyphLenght = fontMetric.boundingRect(string).width();

    for (int r = 0; r < rowCount(); ++r) {
        auto row = _cellData.at(r);
        auto data = row.at(column);

        string = QString::number(data);

        auto glyphLenght = fontMetric.boundingRect(string).width();

        resultingGlyphLenght = glyphLenght > resultingGlyphLenght ? glyphLenght :
                                                                    resultingGlyphLenght;
    }

    if(resultingGlyphLenght < 25)
        return defaultCellWidth *scale();

    return resultingGlyphLenght * scale();
}

double ScoreDataModel::columnHeightAt(const int &column, const QString &fontFamily, const int &pointSize) const
{
    auto font = QFont(fontFamily,pointSize);

    QFontMetrics fontMetric(font);

    QString string;

    if(_horizontalHeaderData.count() <= column){

        if(fillMode() == HeaderFillMode::IncrementingIntegerFill)
            string = QString::number(column + 1);
        else
            return defaultCellHeight;
    }
    else
        string = _horizontalHeaderData.at(column);


    auto glyphLenght = fontMetric.boundingRect(string).height();

    return glyphLenght *scale();
}

double ScoreDataModel::rowHeightAt(const int &row, const QString &fontFamily ,const int &pointSize) const
{
    if(_cellData.count() <= 0)
        return 0;

    auto font = QFont(fontFamily,pointSize);
    QFontMetrics fontMetric(font);
    QString string;

    if(_verticalHeaderData.count() <= row)
    {
        if(fillMode() == HeaderFillMode::IncrementingIntegerFill)
            string = QString::number(row + 1);
        else
            return defaultCellHeight;
    }
    else
        string = _verticalHeaderData.at(row);

    auto resultingGlyphLenght = fontMetric.boundingRect(string).height();

    for (int c = 0; c < columnCount(); ++c) {
        auto cellRow = _cellData.at(row);
        auto data = cellRow.at(c);
        auto dataString = QString::number(data);
        auto glyphLenght = fontMetric.boundingRect(dataString).height();
        resultingGlyphLenght = glyphLenght > resultingGlyphLenght ? glyphLenght : resultingGlyphLenght;
    }

    if(resultingGlyphLenght < 25)
        resultingGlyphLenght = 25;

    return resultingGlyphLenght;
}

double ScoreDataModel::rowWidthAt(const int &row, const QString &fontFamily, const int &pointSize) const
{
    auto font = QFont(fontFamily,pointSize);

    QFontMetrics fontMetric(font);

    QString string;

    if(_verticalHeaderData.count() <= row)
    {
        if(fillMode() == HeaderFillMode::IncrementingIntegerFill)
            string = QString::number(row + 1);
        else
            return defaultCellWidth;
    }
    else
        string = _verticalHeaderData.at(row);


    auto glyphLenght = fontMetric.boundingRect(string).width();

    return glyphLenght * scale();
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
    if(!index.isValid() || _cellData.count() <= 0)
        return QVariant();
    auto dataRow = _cellData.at(index.row());
    if(index.column() >= dataRow.count())
        return QVariant();
    if(role != Qt::DisplayRole)
        return QVariant();
    auto data = dataRow.at(index.column());
    return data >= 0 ?
                data :
                QVariant("-");
}

QVariant ScoreDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    auto horizontalHeaderCount = _horizontalHeaderData.count();
    int roundIndex = (section - 1)/_numberOfThrows;

    switch (orientation) {
        case Qt::Horizontal : return section == 0 ? 0 : section < horizontalHeaderCount ?
                        _horizontalHeaderData.at(section) : fillMode() == HeaderFillMode::IncrementingIntegerFill ?
                            QVariant(roundIndex + 1) : QVariant();
        case Qt::Vertical : return section < _verticalHeaderData.count() ?
                        _verticalHeaderData.at(section) :  fillMode() == HeaderFillMode::IncrementingIntegerFill ?
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

    auto r = _cellData.at(row);

    r.replace(column,value.toInt());

    _cellData.replace(row,r);

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
        QList<int> dataRow = [this]
        {
            QList<int> resultingList;
            auto count = columnCount(QModelIndex(QModelIndex()));
            for (int i = 0; i < count; ++i)
                resultingList << -1;
            return resultingList;
        }();

        _cellData.insert(row,dataRow);
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
        _cellData.removeAt(i);
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

    for (auto &row : _cellData) {
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

    if(_cellData.count() < 1)
        return;
    auto orientation = _headerOrientation;
    auto initialValue = this->initialValue();
    if(orientation == Qt::Horizontal)
    {
        auto firstColumn = _cellData.at(0);
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
        auto dataRow = _cellData.at(index);

        for (int col = 0; col < columnCount(QModelIndex()); ++col) {
            auto cellValue = dataRow.at(col);

            if(cellValue == -1)
                return col - 1;
        }

        return columnCount() - 1;
    }
    else if(orientation == Qt::Horizontal)
    {
        for (int row = 0; row < rowCount(); ++row) {
            auto dataRow = _cellData.at(row);
            auto data = dataRow.at(index);
            if(data == -1)
                return row -1;
        }
        return rowCount() - 1;
    }
    else
        return -1;
}

int ScoreDataModel::rowCount(const int &column)
{
    for (int row = 0; row < _cellData.count(); ++row) {
        auto dataRow = _cellData.at(row);
        if(dataRow.count() < column && dataRow.at(column) == -1)
            return row;
    }
    return rowCount();
}

bool ScoreDataModel::isColumnEmpty(const int &col)
{
    if(col < 0 || col >= columnCount())
        throw std::out_of_range("Index out of range");

    for (auto dataRow : _cellData) {
        auto cellData = dataRow.at(col);
        if(cellData != -1)
            return false;
    }
    return true;
}

bool ScoreDataModel::isRowEmpty(const int &row)
{
    if(row < 0 || row >= rowCount())
        throw std::out_of_range("Index out of range");
    auto dataRow = _cellData.at(row);
    for (auto data : dataRow) {
        if(data != -1)
            return false;
    }
    return true;
}

int ScoreDataModel::removeData(const QModelIndex &index)
{
    if(!index.isValid())
        return -1;
    auto row = index.row();
    auto column = index.column();
    auto dataRow = _cellData.at(row);
    auto data = dataRow.at(column);
    dataRow.replace(column,-1);
    _cellData.replace(row,dataRow);
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
    return data;
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

int ScoreDataModel::fillMode() const
{
    return _fillMode;
}

void ScoreDataModel::setFillMode(int fillMode)
{
    _fillMode = fillMode;
    emit fillModeChanged();
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
