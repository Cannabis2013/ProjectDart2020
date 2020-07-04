#include "customtablemodel.h"

CustomTableModel::CustomTableModel()
{
}

bool CustomTableModel::addData(int row, int column, int data)
{
    auto dataIndex = this->createIndex(row,column);

    if(!dataIndex.isValid())
        return false;

    try {
        return setData(dataIndex,QVariant(data),Qt::DisplayRole);
    } catch (std::out_of_range *e) {
        printf("%s\n",e->what());
        return false;
    }
}

bool CustomTableModel::appendData(const QString &playerName, const int &data, const int &headerOrientation)
{
    auto index = indexOfHeaderItem(playerName,headerOrientation);
    if(headerOrientation == Qt::Horizontal)
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
    else if(headerOrientation == Qt::Vertical)
    {
        auto rowCount = _cellData.count();
        auto column = index < rowCount ? indexOfLastDecoratedRow(index) : 0;
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

void CustomTableModel::appendHeaderItem(const QVariant &data, const int &orientation)
{
    if(orientation == Qt::Horizontal)
        _horizontalHeaderData.append(data.toString());
    else
        _verticalHeaderData.append(data.toString());

    emit dataChanged(QModelIndex(),QModelIndex());
}

QString CustomTableModel::headerData(const int &index, const int &orientation) const
{
    auto value =  headerData(index,static_cast<Qt::Orientation>(orientation),Qt::DisplayRole).toString();

    return value;
}

int CustomTableModel::headerItemCount(const int &orientation) const
{
    if(orientation == Qt::Horizontal)
        return _horizontalHeaderData.count();
    else
        return _verticalHeaderData.count();
}

int CustomTableModel::rowCount() const
{
    return rowCount(QModelIndex());
}

int CustomTableModel::columnCount() const
{
    return columnCount(QModelIndex());
}

double CustomTableModel::columnWidthAt(const int &column, const QString &fontFamily, const int &pointSize) const
{
    if(column >= columnCount())
        throw std::out_of_range("Index out of range");

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

double CustomTableModel::columnHeightAt(const int &column, const QString &fontFamily, const int &pointSize) const
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

double CustomTableModel::rowHeightAt(const int &row, const QString &fontFamily ,const int &pointSize) const
{
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

double CustomTableModel::rowWidthAt(const int &row, const QString &fontFamily, const int &pointSize) const
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

int CustomTableModel::horizontalHeaderCount() const
{
    return _horizontalHeaderData.count();
}

int CustomTableModel::verticalHeaderCount() const
{
    return _verticalHeaderData.count();
}

int CustomTableModel::rowCount(const QModelIndex &) const
{
    return _rows;
}

int CustomTableModel::columnCount(const QModelIndex &) const
{
    return _columns;
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= _cellData.count())
        return QVariant();

    auto rowData = _cellData.at(index.row());

    if(index.column() >= rowData.count())
        return QVariant();

    if(role != Qt::DisplayRole)
        return QVariant();

    auto data = rowData.at(index.column());

    return data >= 0 ?
                data :
                QVariant();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    auto numberOfColumns = columnCount();
    auto horizontalHeaderCount = _horizontalHeaderData.count();

    switch (orientation) {
        case Qt::Horizontal : return section < numberOfColumns ?
                    horizontalHeaderCount > section ?
                        _horizontalHeaderData.at(section) : fillMode() == HeaderFillMode::IncrementingIntegerFill ?
                            QVariant(section + 1) : QVariant() : QVariant();
        case Qt::Vertical : return section < _verticalHeaderData.count() ?
                    _verticalHeaderData.count() >= section  ?
                        _verticalHeaderData.at(section) : fillMode() == HeaderFillMode::IncrementingIntegerFill ?
                            QVariant(section + 1) : QVariant(): QVariant();
        default: return QVariant();
    }
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto row = index.row();
    auto column = index.column();

    if(row < 0 || column < 0)
        return false;
    /*
    if(row >= _verticalHeaderData.count())
        throw new std::out_of_range("You need to allocate corresponding header rows before adding new data rows");
    */
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

bool CustomTableModel::insertRows(int row, int count, const QModelIndex &)
{
    auto firstRow = row <= rowCount(QModelIndex()) ? row : rowCount(QModelIndex()) - 1;
    auto lastRow  =  row <= rowCount(QModelIndex()) ? firstRow + count : 2*row + count - firstRow;
    auto c = row <= rowCount(QModelIndex()) ? count : count + (row - firstRow) - 1;

    beginInsertRows(QModelIndex(),firstRow,lastRow);

    for (int i = 0; i < c; ++i) {
        QList<int> rowData = [this]
        {
            QList<int> resultingList;
            for (int i = 0; i < columnCount(QModelIndex()); ++i)
                resultingList << -1;
            return resultingList;
        }();

        _cellData.insert(row,rowData);
    }

    endInsertRows();

    _rows += c;

    return true;
}

bool CustomTableModel::insertColumns(int column, int count, const QModelIndex &)
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

    return true;
}

bool CustomTableModel::removeRows(int row, int count, const QModelIndex &)
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

    // Notify model and surrounding state that data has changed
    emit dataChanged(topLeftIndex,bottomRightIndex,{Qt::DisplayRole});

    return true;
}

bool CustomTableModel::removeColumns(int column, int count, const QModelIndex &)
{
    // Check if input satisfies model constraints
    if(column < 0 || column >= columnCount())
        return false;

    // Create bounding indexes
    auto topLeftIndex = createIndex(0,column);
    auto bottomRightIndex = createIndex(rowCount() - 1,column + count);

    // Begin remove columns
    beginRemoveColumns(QModelIndex(),column,column + count);

    for (auto &row : _cellData) {
        for (int i = column; i < column + column; ++i)
            row.removeAt(i);
    }

    endRemoveColumns();

    // Notify model and surrounding state that data has changed
    emit dataChanged(topLeftIndex,bottomRightIndex,{Qt::DisplayRole});

    return true;
}

int CustomTableModel::indexOfLastDecoratedRow(const int &row)
{
    auto r = _cellData.at(row);

    for (int i = 0; i < columnCount(QModelIndex()); ++i) {
        auto cellValue = r.at(i);

        if(cellValue == -1)
            return i;
    }

    return columnCount();
}

int CustomTableModel::indexOfLastDecoratedColumn(const int &column)
{
    for (int row = 0; row < rowCount(); ++row) {
        auto rowData = _cellData.at(row);
        auto data = rowData.at(column);
        if(data == -1)
            return row;
    }

    return rowCount();
}

int CustomTableModel::rowCount(const int &column)
{
    for (int row = 0; row < _cellData.count(); ++row) {
        auto rowData = _cellData.at(row);
        if(rowData.count() <= column)
            return row;
    }
    return rowCount();
}

int CustomTableModel::indexOfHeaderItem(const QString &data, const int &orientation)
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

int CustomTableModel::fillMode() const
{
    return _fillMode;
}

void CustomTableModel::setFillMode(int fillMode)
{
    _fillMode = fillMode;
    emit fillModeChanged();
}

int CustomTableModel::preferedCellWidth(const QString &fontFamily, const int &pointSize) const
{
    auto preferedWidth = 0;
    for (auto txt : _verticalHeaderData) {
        QFontMetrics metrics(QFont(fontFamily,pointSize));

        auto glypLenght = metrics.boundingRect(txt).width();

        preferedWidth = glypLenght > preferedWidth ? glypLenght : preferedWidth;
    }

    return preferedWidth;
}

double CustomTableModel::scale() const
{
    return _scale;
}

void CustomTableModel::setScale(double scale)
{
    _scale = scale;
}
