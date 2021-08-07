#ifndef IHEADERLABELS_H
#define IHEADERLABELS_H

#include <qvector.h>
template<typename  T>
class IHeaderLabels
{
public:
    virtual void appendItem(const T &item) = 0;
    virtual void appendItems(const QVector<T> &items) = 0;
    virtual void removeItem(const int &index) = 0;
    virtual void clear() = 0;
    virtual int indexOf(const T &item) const = 0;
    virtual int count() const = 0;
    virtual T item(const int &index) const = 0;
    virtual QVector<T> items() const = 0;
};

#endif // IHEADERLABELS_H
