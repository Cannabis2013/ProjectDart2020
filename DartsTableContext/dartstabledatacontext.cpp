#include "dartstabledatacontext.h"

void DartsTableDataContext::addItem(const Index &index, const Item &item)
{
    auto r = _data.at(index.row());
    r.insert(index.column(),item);
    _data.replace(index.row(),r);
}

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
    if(!index.isValid() || _data.empty())
        return Item();
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

