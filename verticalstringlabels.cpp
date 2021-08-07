#include "verticalstringlabels.h"

void VerticalStringLabels::appendItem(const QString &item)
{
    _header.append(item);
    emit dataChanged();
}

void VerticalStringLabels::appendItems(const QVector<QString> &items)
{
    _header.append(items);
    emit dataChanged();
}

void VerticalStringLabels::removeItem(const int &index)
{
    if(!isValid(index))
        throw OUT_OF_RANGE_MSG;
    _header.remove(index);
    emit dataChanged();
}

void VerticalStringLabels::clear()
{
    _header.clear();
    emit dataChanged();
}

int VerticalStringLabels::indexOf(const QString &item) const
{
    if(!isValid(item))
        throw ITEM_NOT_FOUND_MSG;
    return _header.indexOf(item);
}

int VerticalStringLabels::count() const
{
    return _header.count();
}

QString VerticalStringLabels::item(const int &index) const
{
    if(!isValid(index))
        throw OUT_OF_RANGE_MSG;
    return _header.at(index);
}

QVector<QString> VerticalStringLabels::items() const
{
    return _header;
}

bool VerticalStringLabels::isValid(const int &index) const
{
    return index >= 0 && index < _header.count();
}

bool VerticalStringLabels::isValid(const QString &item) const
{
    return _header.contains(item);
}
