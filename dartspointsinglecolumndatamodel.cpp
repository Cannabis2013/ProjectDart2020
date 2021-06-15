#include "dartspointsinglecolumndatamodel.h"

using namespace DartsDataModelsContext;

bool DartsPointSingleColumnDataModel::insertData(const QString &playerName,
                                                 const int &point,
                                                 const int &score)
{
    auto model = _pointModelBuilderService->buildModelByValues(point,score);
    auto indexOfPlayer = indexOfHeaderItem(playerName);
    auto modelIndex = this->createIndex(indexOfPlayer,0);
    if(!modelIndex.isValid())
        return false;
    try {
        setDataAtIndex(modelIndex,model);
    } catch (std::out_of_range *e) {
        printf("%s\n",e->what());
        return false;
    }
    return true;
}

bool DartsPointSingleColumnDataModel::removeLastItem(const QString &playerName)
{
    auto column = indexOfHeaderItem(playerName);
    auto row = indexOfLastDecoratedField();
    auto index = createIndex(row,column);
    auto result = removeData(index);
    return result;
}

void DartsPointSingleColumnDataModel::appendHeaderItem(const QVariant &data)
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

void DartsPointSingleColumnDataModel::clearData()
{
    _data.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    _columns = 1;
    _rows = 0;
    _verticalHeaderData.clear();
    emit dataChanged(createIndex(0,0),bottomRight);
}

QString DartsPointSingleColumnDataModel::getHeaderData(const int &index) const
{
    auto value = headerData(index,Qt::Vertical,Qt::DisplayRole).toString();
    return value;
}

int DartsPointSingleColumnDataModel::headerItemCount() const
{
    auto count = _verticalHeaderData.count();
    return count;
}

int DartsPointSingleColumnDataModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int DartsPointSingleColumnDataModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double DartsPointSingleColumnDataModel::columnWidthAt(const int &column)
{
    Q_UNUSED(column);
    return _columnWidth;
}

double DartsPointSingleColumnDataModel::rowHeightAt(const int &row) const
{
    if(_data.count() <= 0)
        return 0;
    auto headerDataGlypHeight = rowHeightFromHeaderData(row);
    auto cellDataHeight = rowHeightFromCellDataAt(row);
    auto result = headerDataGlypHeight > cellDataHeight ? headerDataGlypHeight :
                                                          cellDataHeight;
    return result;
}

int DartsPointSingleColumnDataModel::verticalHeaderCount() const
{
    return _verticalHeaderData.count();
}

int DartsPointSingleColumnDataModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int DartsPointSingleColumnDataModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

int DartsPointSingleColumnDataModel::columnWidth() const
{
    return _columnWidth;
}

QVariant DartsPointSingleColumnDataModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || _data.count() <= 0)
        return QVariant();
    if(role != Qt::DisplayRole)
        return QVariant();
    auto row = index.row();
    auto pointModel = _data.at(row);
    auto json = _convertPointToJsonService->toJson(pointModel);
    return pointModel->score() >= 0 ?
                json :
                QVariant("");
}

QVariant DartsPointSingleColumnDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if(role != Qt::DisplayRole)
        return QVariant();
    return _verticalHeaderData.at(section);
}

bool DartsPointSingleColumnDataModel::setDataAtIndex(const QModelIndex &index, const IDataModelPoint* &pointModel)
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
    _data.replace(row,pointModel);
    // Update column width from column by the size of its data
    setColumnWidthByData(pointModel->score());
    emit dataChanged(index,index);
    return true;
}

bool DartsPointSingleColumnDataModel::setData(const QModelIndex &index, const QVariant &data, int role)
{

    return true;
}

bool DartsPointSingleColumnDataModel::insertRows(int row, int count, const QModelIndex &)
{
    auto firstRow = row <= rowCount(QModelIndex()) ? row : rowCount(QModelIndex()) - 1;
    auto lastRow  =  row <= rowCount(QModelIndex()) ? firstRow + count : 2*row + count - firstRow;
    auto c = row <= rowCount(QModelIndex()) ? count : count + (row - firstRow) - 1;
    beginInsertRows(QModelIndex(),firstRow,lastRow);
    auto columnCount = this->columnCount();
    for (int i = 0; i < count; ++i)
        _data.append(_pointModelBuilderService->buildDefaultPointModel());
    endInsertRows();
    _rows += c;
    emit dataChanged(createIndex(row,0),createIndex(lastRow,columnCount));
    return true;
}

bool DartsPointSingleColumnDataModel::insertColumns(int column, int count, const QModelIndex &)
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

bool DartsPointSingleColumnDataModel::removeRows(int row, int count, const QModelIndex &)
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

bool DartsPointSingleColumnDataModel::removeColumns(int column, int count, const QModelIndex &)
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

void DartsPointSingleColumnDataModel::updateInitialCellValues()
{

    if(_data.count() < 1)
        return;
    auto initialValue = this->initialValue();
    for (int i = 0; i < columnCount(); ++i)
        setData(createIndex(0,i),initialValue,Qt::DisplayRole);
}

void DartsPointSingleColumnDataModel::setColumnWidthByData(const int& data)
{
    auto scoreGlypWidth = stringWidth(QString::number(data),
                                      scoreFontFamily(),
                                      scoreFontSize());
    if(scoreGlypWidth > _columnWidth)
        _columnWidth = scoreGlypWidth;
}

double DartsPointSingleColumnDataModel::rowHeightFromHeaderData(const int &row) const
{

    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),headerFontSize()));
    auto headerData = _verticalHeaderData.at(row);
    auto headerDataGlyphHeight = scoreFontMetric.boundingRect(headerData).height();
    if(headerDataGlyphHeight < minimumPreferedRowHeight)
        return minimumPreferedRowHeight;
    return headerDataGlyphHeight;
}

double DartsPointSingleColumnDataModel::rowHeightFromCellDataAt(const int &row) const
{
    auto scoreFontMetric = QFontMetrics(QFont(scoreFontFamily(),scoreFontSize()));
    auto pointFontMetric = QFontMetrics(QFont(pointFontFamily(),pointFontSize()));
    auto columnData = _data.at(row);
    auto pointString = QString::number(columnData->point());
    auto scoreString = QString::number(columnData->score());
    auto scoreGlyphHeight = scoreFontMetric.boundingRect(scoreString).height();
    auto pointGlyphHeight = pointFontMetric.boundingRect(pointString).height();
    auto summedHeight = scoreGlyphHeight + pointGlyphHeight;
    if(summedHeight < minimumPreferedRowHeight)
        return minimumPreferedRowHeight;
    return summedHeight;
}

void DartsPointSingleColumnDataModel::initializeFieldsHorizontally(const int &startColumn)
{
    auto dataCount = _data.count();
    if(startColumn < dataCount)
        return;
    auto lastDecoratedField = indexOfLastDecoratedField();
    auto count = startColumn - lastDecoratedField;

    for (int i = 0; i < count; ++i)
        _data.append(_pointModelBuilderService->buildDefaultPointModel());
}

bool DartsPointSingleColumnDataModel::isIndexValid(const QModelIndex &index)
{
    auto row = index.row();
    auto column = index.column();
    if(row > 0)
        return false;
    else if(column >= _data.count())
        return false;
    return true;
}

bool DartsPointSingleColumnDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}


int DartsPointSingleColumnDataModel::indexOfLastDecoratedField()
{
    auto lastDecoratedField = _data.count() - 1;
    return lastDecoratedField;
}


bool DartsPointSingleColumnDataModel::isRowEmpty(const int &row)
{
    if(row < 0 || row >= rowCount())
        throw std::out_of_range("Index out of range");
    for (int i = 0; i < _data.count(); ++i) {
        auto data = _data.at(i);
        if(data->point() != -1 && data->score() != -1)
            return false;
    }
    return true;
}

bool DartsPointSingleColumnDataModel::removeData(const QModelIndex &index)
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

int DartsPointSingleColumnDataModel::indexOfHeaderItem(const QString &data)
{
    auto index = _verticalHeaderData.indexOf(data);
    return index;
}

void DartsPointSingleColumnDataModel::addVerticalHeaderData(const QString &data)
{
    _verticalHeaderData.append(data);
    emit dataChanged(QModelIndex(),QModelIndex());
}

int DartsPointSingleColumnDataModel::stringWidth(const QString &string, const QString &family, const int &pointSize) const
{
    auto fontMetric = QFontMetrics(QFont(family,pointSize));
    auto r = fontMetric.boundingRect(string).width();
    return r;
}

int DartsPointSingleColumnDataModel::headerFontSize() const
{
    return _headerFontSize;
}

void DartsPointSingleColumnDataModel::setHeaderFontSize(int headerFontSize)
{
    _headerFontSize = headerFontSize;
}

QStringList DartsPointSingleColumnDataModel::getVerticalHeaderData() const
{
    return _verticalHeaderData;
}

void DartsPointSingleColumnDataModel::setVerticalHeaderData(const QList<QString> &horizontalHeaderData)
{
    _verticalHeaderData = horizontalHeaderData;
}

QString DartsPointSingleColumnDataModel::pointFontFamily() const
{
    return _pointFontFamily;
}

void DartsPointSingleColumnDataModel::setPointFontFamily(const QString &pointFontFamily)
{
    _pointFontFamily = pointFontFamily;
}

QString DartsPointSingleColumnDataModel::scoreFontFamily() const
{
    return _scoreFontFamily;
}

void DartsPointSingleColumnDataModel::setScoreFontFamily(const QString &scoreFontFamily)
{
    _scoreFontFamily = scoreFontFamily;
}

int DartsPointSingleColumnDataModel::pointFontSize() const
{
    return _pointFontSize;
}

void DartsPointSingleColumnDataModel::setPointFontSize(int pointFontSize)
{
    _pointFontSize = pointFontSize;
}

int DartsPointSingleColumnDataModel::scoreFontSize() const
{
    return _scoreFontSize;
}

void DartsPointSingleColumnDataModel::setScoreFontSize(int scoreFontSize)
{
    _scoreFontSize = scoreFontSize;
}

int DartsPointSingleColumnDataModel::initialValue() const
{
    return _initialValue;
}

void DartsPointSingleColumnDataModel::setInitialValue(int initialValue)
{
    _initialValue = initialValue;
    updateInitialCellValues();
}

int DartsPointSingleColumnDataModel::minimumRowCount() const
{
    return _minimumRowCount;
}

void DartsPointSingleColumnDataModel::setMinimumRowCount(int minimumRowCount)
{
    Q_UNUSED(minimumRowCount);
    return;
}

int DartsPointSingleColumnDataModel::minimumColumnCount() const
{
    return _minimumColumnCount;
}

void DartsPointSingleColumnDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    Q_UNUSED(minimumColumnCount);
    return;
}

int DartsPointSingleColumnDataModel::preferedHeaderItemWidth() const
{
    auto itemWidth = greatestVerticalHeaderWidth*_scale;
    return itemWidth;
}

void DartsPointSingleColumnDataModel::setColumnCount(const int &count)
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

void DartsPointSingleColumnDataModel::setRowCount(const int &count)
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

double DartsPointSingleColumnDataModel::scale() const
{
    return _scale;
}

void DartsPointSingleColumnDataModel::setScale(double scale)
{
    _scale = scale;
}

int DartsPointSingleColumnDataModel::horizontalHeaderFillMode() const
{
    return _horizontalFillMode;
}

void DartsPointSingleColumnDataModel::setHorizontalHeaderFillMode(const int &fillMode)
{
    _horizontalFillMode = fillMode;
    emit fillModeChanged();
}
