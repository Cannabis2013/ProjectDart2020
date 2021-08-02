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

bool DartsPointMultiColumnDataModel::insertData(const QString &playerName,const int &point,const int &score)
{
    auto modelIndex = createIndexFromPlayerName(playerName);
    try {
        setData(modelIndex,QVariant::fromValue<PointInputModel>(PointInputModel(point,score)),Qt::DisplayRole);
    } catch (std::out_of_range *e) {
        printf("%s\n",e->what());
        return false;
    }
    return true;
}

bool DartsPointMultiColumnDataModel::setPlayerData(const QString &playerName, const int &point, const int &score)
{
    auto indexOfPlayer =  verticalHeaderContext()->headerData().indexOf(playerName);
    auto scorePair = PointInputModel(point,score);
    auto modelIndex = this->createIndex(indexOfPlayer,0);
    if(!modelIndex.isValid())
        return false;
    try {
        setData(modelIndex,QVariant::fromValue<PointInputModel>(scorePair),Qt::DisplayRole);
    } catch (std::out_of_range *e) {
        printf("%s\n",e->what());
        return false;
    }
    return true;
}

bool DartsPointMultiColumnDataModel::removeLastItem(const QString &playerName)
{
    auto row = verticalHeaderContext()->headerData().indexOf(playerName);
    auto column = indexOfLastDecoratedCell(row);
    auto index = createIndex(row,column);
    auto result = removeData(index) != PointInputModel(-1,-1);
    return result;
}

void DartsPointMultiColumnDataModel::appendHeaderItem(const QVariant &data)
{
    auto glyphLength = fontMetricContext()->stringWidth(data.toString(),fontContext()->scoreFontFamily(),headerFontSize());
    if(verticalHeaderContext()->count() >= rowCount())
        insertRows(verticalHeaderContext()->count(),1,QModelIndex());
    else
        emit dataChanged(QModelIndex(),QModelIndex());
    verticalHeaderContext()->addHeaderItem(data.toString());
    if(glyphLength > _verticalHeaderStringWidth)
        setVerticalHeaderStringWidth(glyphLength);
}

void DartsPointMultiColumnDataModel::clearData()
{
    _data.clear();
    auto bottomRight = createIndex(rowCount() - 1,columnCount() - 1);
    tableContext()->setColumns(minimumColumnCount());
    tableContext()->setRows(0);
    verticalHeaderContext()->clear();
    emit dataChanged(createIndex(0,0),bottomRight);
}

QString DartsPointMultiColumnDataModel::getHeaderData(const int &index, const int &orientation) const
{
    auto value = headerData(index,static_cast<Qt::Orientation>(orientation),Qt::DisplayRole).toString();
    return value;
}

int DartsPointMultiColumnDataModel::headerItemCount() const
{
    return verticalHeaderContext()->count();
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
    auto s = fontMetricContext()->scale();
    auto w = columnWidthsAt(column);
    auto columnWidth = s*w;
    if(columnWidth < tableCellContext()->minimumPreferedColumnWidth())
        return tableCellContext()->minimumPreferedColumnWidth();
    else
        return columnWidth;
}

double DartsPointMultiColumnDataModel::rowHeightAt(const int &row) const
{
    if(_data.count() <= 0)
        return 0;
    QString headerString;
    if(verticalHeaderContext()->count() <= row)
        return tableCellContext()->minimumPreferedRowHeight();
    else
        headerString = verticalHeaderContext()->headerData().at(row);
    auto resultingGlyphLenght =  fontMetricContext()->stringHeight(headerString,fontContext()->scoreFontFamily(),fontContext()->scoreFontSize());
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
        auto scoreGlyphHeight = fontMetricContext()->stringHeight(scoreString,fontContext()->scoreFontFamily(),fontContext()->scoreFontSize());
        auto pointGlyphHeight = fontMetricContext()->stringHeight(pointString,fontContext()->pointFontFamily(),fontContext()->pointFontSize());;
        auto totalGlypHeight = scoreGlyphHeight + pointGlyphHeight;
        resultingGlyphLenght = totalGlypHeight > resultingGlyphLenght ? totalGlypHeight : resultingGlyphLenght;
    }
    if(resultingGlyphLenght < tableCellContext()->minimumPreferedRowHeight())
        resultingGlyphLenght = tableCellContext()->minimumPreferedRowHeight();
    return resultingGlyphLenght;
}

int DartsPointMultiColumnDataModel::horizontalHeaderCount() const
{
    return tableContext()->columns();
}

int DartsPointMultiColumnDataModel::verticalHeaderCount() const
{
    return verticalHeaderContext()->headerData().count();
}

int DartsPointMultiColumnDataModel::rowCount(const QModelIndex &) const
{
    return tableContext()->rows();
}

int DartsPointMultiColumnDataModel::columnCount(const QModelIndex &) const
{
    return tableContext()->columns();
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
    if(orientation == Qt::Horizontal)
        return horizontalHeaderContext()->headerDataAt(section);
    else if(section < verticalHeaderCount())
        return verticalHeaderContext()->headerData().at(section);
    else
        return QVariant();
}

int DartsPointMultiColumnDataModel::numberOfAttemps() const
{
    return horizontalHeaderContext()->attemptsPerRound();
}

bool DartsPointMultiColumnDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Check if index is out of bounds
    if(index.row() < 0 || index.column() < 0)
        return false;
    // Create rows and columns if necessary
    createRowsAndColumns(index,numberOfAttemps());
    // add value
    auto model = addValue(index,value);
    // Update corresponding column width
    updateColumnWidth(index,model);
    // Notify external context
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
    tableContext()->incrementRows(c);
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
        newColumnWidths << tableCellContext()->minimumPreferedColumnWidth();

    for (int i = 0; i < newColumnWidths.count(); ++i) {
        auto columnWidth = newColumnWidths.at(i);
        _columnWidths.insert(column,columnWidth);
    }
    endInsertColumns();
    tableContext()->incrementColumns(c);
    emit dataChanged(createIndex(0,firstColumn),
                     createIndex(verticalHeaderContext()->count(),lastColumn));
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
        verticalHeaderContext()->removeHeaderDataAt(i);
    }
    endRemoveRows();
    tableContext()->decrementRows(count);
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
    tableContext()->decrementColumns(count);
    endRemoveColumns();
    emit dataChanged(QModelIndex(),QModelIndex());

    return true;
}

void DartsPointMultiColumnDataModel::updateInitialCellValues()
{

    if(_data.count() < 1)
        return;
    auto initialValue = this->initialValue();
    for (int rowIndex = 0; rowIndex < rowCount(); ++rowIndex)
        setData(createIndex(rowIndex,0),initialValue,Qt::DisplayRole);
}

QModelIndex DartsPointMultiColumnDataModel::createIndexFromPlayerName(const QString &playerName) const
{
    auto index = verticalHeaderContext()->headerData().indexOf(playerName);
    auto rowCount = _data.count();
    auto column = index < rowCount ?
                indexOfLastDecoratedCell(index) + 1 : 0;
    return this->createIndex(index,column);
}

DartsPointMultiColumnDataModel::PointInputModel DartsPointMultiColumnDataModel::addValue(const QModelIndex &index, const QVariant &value)
{
    auto pairs = _data.at(index.row());
    auto newPair = value.value<PointInputModel>();
    pairs.replace(index.column(),newPair);
    _data.replace(index.row(),pairs);
    return newPair;
}

void DartsPointMultiColumnDataModel::updateColumnWidth(const QModelIndex &index, const PointInputModel &model)
{
    auto pointGlypWidth = fontMetricContext()->stringWidth(QString::number(model.first),fontContext()->pointFontFamily(),
                                                       fontContext()->pointFontSize());
    auto scoreGlypWidth = fontMetricContext()->stringWidth(QString::number(model.second),fontContext()->scoreFontFamily(),
                                                       fontContext()->scoreFontSize());
    int totalGlyphWidth = pointGlypWidth + scoreGlypWidth;
    if(totalGlyphWidth > columnWidthsAt(index.column()))
        setColumnWidthAt(index.column(),totalGlyphWidth);
}

void DartsPointMultiColumnDataModel::createRowsAndColumns(const QModelIndex &index, const int &delta)
{
    if(index.row() >= rowCount())
        insertRows(index.row(),delta,QModelIndex());
    if(index.column() >= columnCount())
        insertColumns(index.column(),delta,QModelIndex());
}

bool DartsPointMultiColumnDataModel::isCellDecorated(const QModelIndex &index)
{
    return data(index,Qt::DisplayRole) != "-";
}

int DartsPointMultiColumnDataModel::indexOfLastDecoratedCell(const int &index) const
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

    for (auto pairsRow : qAsConst(_data)) {
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
    auto rowData = _data.at(row);
    auto columnData = rowData.at(column);
    auto initialPair = PointInputModel(-1,-1);
    rowData.replace(column,initialPair);
    _data.replace(row,rowData);
    if(isColumnEmpty(column) && column > minimumColumnCount())
    {
        removeColumns(column,1,QModelIndex());
        return columnData;
    }
    emit dataChanged(createIndex(row,column),createIndex(row,column));
    return columnData;
}

void DartsPointMultiColumnDataModel::setVerticalHeaderStringWidth(double verticalHeaderStringWidth)
{
    _verticalHeaderStringWidth = verticalHeaderStringWidth;
}

int DartsPointMultiColumnDataModel::headerFontSize() const
{
    return headerStylistics()->fontSize();
}

void DartsPointMultiColumnDataModel::setHeaderFontSize(int headerFontSize)
{
    headerStylistics()->setFontSize(headerFontSize);
}

QVector<QString> DartsPointMultiColumnDataModel::getVerticalHeaderData() const
{
    return verticalHeaderContext()->headerData();
}

void DartsPointMultiColumnDataModel::setVerticalHeaderData(const QVector<QString> &verticalHeaderData)
{
    verticalHeaderContext()->setHeaderData(verticalHeaderData);
}

int DartsPointMultiColumnDataModel::initialValue() const
{
    return horizontalHeaderContext()->initialValue();
}

void DartsPointMultiColumnDataModel::setInitialValue(int initialValue)
{
    horizontalHeaderContext()->setInitialValue(initialValue);
    emit initialValueChanged();
}

int DartsPointMultiColumnDataModel::minimumRowCount() const
{
    return tableContext()->minimumRowCount();
}

void DartsPointMultiColumnDataModel::setMinimumRowCount(int minimumRowCount)
{
    tableContext()->setMinimumRowCount(minimumRowCount);

    auto rowCount = this->rowCount();
    if(minimumRowCount > rowCount)
        setRowCount(minimumRowCount);
}

int DartsPointMultiColumnDataModel::minimumColumnCount() const
{
    return tableContext()->minimumColumnCount();
}

void DartsPointMultiColumnDataModel::setMinimumColumnCount(int minimumColumnCount)
{
    tableContext()->setMinimumColumnCount(minimumColumnCount);
    auto colCount = columnCount();
    if(minimumColumnCount > colCount)
        setColumnCount(minimumColumnCount);
    emit minimumColumnCountChanged();
}

int DartsPointMultiColumnDataModel::preferedHeaderItemWidth() const
{
    auto scale = fontMetricContext()->scale();
    auto preferedWidth =  _verticalHeaderStringWidth*scale;
    return preferedWidth;
}

void DartsPointMultiColumnDataModel::setNumberOfAttemps(const int &count)
{
    horizontalHeaderContext()->setAttemptsPerRound(count);
    emit dataChanged(QModelIndex(),QModelIndex());
}

double DartsPointMultiColumnDataModel::scale() const
{
    return fontMetricContext()->scale();
}

void DartsPointMultiColumnDataModel::setScale(const double &scale)
{
    fontMetricContext()->setScale(scale);
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
