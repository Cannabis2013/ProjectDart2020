#include "stringlabelsmodel.h"

void StringLabelsModel::setItem(const QString &item, const int &index)
{
    _header.replace(index,item);
    emit dataChanged();
}

void StringLabelsModel::appendItem(const QString &item)
{
    _header.append(item);
    emit dataChanged();
}

void StringLabelsModel::appendItems(const QVector<QString> &items)
{
    _header.append(items);
    emit dataChanged();
}

void StringLabelsModel::removeItem(const int &index)
{
    if(!isValid(index))
        throw OUT_OF_RANGE_MSG;
    _header.remove(index);
    emit dataChanged();
}

void StringLabelsModel::clear()
{
    _header.clear();
    emit dataChanged();
}

int StringLabelsModel::indexOf(const QString &item) const
{
    if(!isValid(item))
        throw ITEM_NOT_FOUND_MSG;
    return _header.indexOf(item);
}

int StringLabelsModel::count() const
{
    return _header.count();
}

QString StringLabelsModel::item(const int &index) const
{
    if(!isValid(index))
        throw OUT_OF_RANGE_MSG;
    return _header.at(index);
}

QVector<QString> StringLabelsModel::items() const
{
    return _header;
}

bool StringLabelsModel::isValid(const int &index) const
{
    return index >= 0 && index < _header.count();
}

bool StringLabelsModel::isValid(const QString &item) const
{
    return _header.contains(item);
}
