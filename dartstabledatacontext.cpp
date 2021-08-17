#include "dartstabledatacontext.h"
using namespace TableDataContext;

DartsTableDataContext::Rows DartsTableDataContext::data() const
{
    return _data;
}

DartsTableDataContext::Rows &DartsTableDataContext::rows()
{
    return _data;
}

void DartsTableDataContext::replaceItem(const Index &index, const Item &model)
{
    auto dataRow = _data.at(index.row());
    dataRow.replace(index.column(),model);
    _data.replace(index.row(),dataRow);
}

DartsTableDataContext::Row DartsTableDataContext::rowAt(const int &row) const
{
    return _data.at(row);
}

DartsTableDataContext::Item DartsTableDataContext::item(const Index &index) const
{
    auto dataRow = _data.at(index.row());
    return dataRow.at(index.column());
}

void DartsTableDataContext::clear()
{
    _data.clear();
}

int DartsTableDataContext::rowCount() const
{
    return _data.count();
}

void DartsTableDataContext::replaceRow(const int &row, const Row &data)
{
    _data.replace(row,data);
}

void DartsTableDataContext::checkIndexCompliance(const int &subject, const int &limit) const
{
    if(subject >= limit || subject < 0)
        throw std::out_of_range(err);
}

bool DartsTableDataContext::hasColumns(const int &column, const Row &r) const
{
    return column < r.count();
}

int DartsTableDataContext::lastFilledCell(const int &row, const int &columnCount, const Rows &data) const
{
    try {
        checkIndexCompliance(row,data.count());
        auto rowData = data.at(row);
        for (int col = 0; col < columnCount; ++col) {
            auto columnData = rowData.at(col);
            auto point = columnData.first;
            if(point == -1)
                return col - 1;
        }
        return columnCount - 1;
    }  catch (const char *msg) {
        qDebug() << msg;
        return false;
    }
}

bool DartsTableDataContext::isColumnEmpty(const int &column, const int &columnsCount, const Rows &data) const
{
    try {
        checkIndexCompliance(column,columnsCount);
        for (auto pairsRow : qAsConst(data)) {
            auto pair = pairsRow.at(column);
            auto point = pair.first;
            if(point != -1)
                return false;
        }
        return true;
    }  catch (const char *msg) {
        qDebug() << msg;
        return false;
    }
}
