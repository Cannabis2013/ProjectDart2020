#ifndef ITABLEHEADERCONTEXT_H
#define ITABLEHEADERCONTEXT_H

#include <qvector.h>
template<typename T>
class ITableHeaderContext
{
public:
    virtual QVector<T> headerData() const = 0;
    virtual void removeHeaderDataAt(const int &index) = 0;
    virtual void clear() = 0;
    virtual int count() const = 0;
    virtual void setHeaderData(const QVector<T> &data) = 0;
    virtual void addHeaderItem(const T &data) = 0;
};
#endif // IDATAMODELHEADERDATA_H

