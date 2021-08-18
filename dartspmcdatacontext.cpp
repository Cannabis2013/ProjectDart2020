#include "dartspmcdatacontext.h"

DartsPMCDataContext::Rows DartsPMCDataContext::data() const
{
    return _data;
}

DartsPMCDataContext::Rows &DartsPMCDataContext::rows()
{
    return _data;
}

void DartsPMCDataContext::replaceItem(const Index &index, const Item &model)
{
    auto dataRow = _data.at(index.row());
    dataRow.replace(index.column(),model);
    _data.replace(index.row(),dataRow);
}

DartsPMCDataContext::Row DartsPMCDataContext::rowAt(const int &row) const
{
    return _data.at(row);
}

DartsPMCDataContext::Item DartsPMCDataContext::item(const Index &index) const
{
    if(!index.isValid() || _data.empty())
        return Item();
    auto dataRow = _data.at(index.row());
    return dataRow.at(index.column());
}

void DartsPMCDataContext::clear()
{
    _data.clear();
}

int DartsPMCDataContext::rowCount() const
{
    return _data.count();
}

void DartsPMCDataContext::replaceRow(const int &row, const Row &data)
{
    _data.replace(row,data);
}

