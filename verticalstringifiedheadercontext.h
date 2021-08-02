#ifndef VERTICALSTRINGIFIEDHEADERCONTEXT_H
#define VERTICALSTRINGIFIEDHEADERCONTEXT_H

#include "itableheadercontext.h"
#include <qstring.h>

class VerticalStringifiedHeaderContext : public ITableHeaderContext<QString>
{
public:
    virtual QVector<QString> headerData() const override
    {
        return _verticalHeaderData;
    }
    virtual void addHeaderItem(const QString &data) override
    {
        _verticalHeaderData.append(data);
    }
    virtual void setHeaderData(const QVector<QString> &data) override
    {
        _verticalHeaderData = data;
    }
    virtual int count() const override
    {
        return _verticalHeaderData.count();
    }
    virtual void clear() override
    {
        _verticalHeaderData.clear();
    }
    virtual void removeHeaderDataAt(const int &index) override
    {
        _verticalHeaderData.remove(index);
    }
private:
    QVector<QString> _verticalHeaderData;
};

#endif // DEFAULTHEADERSTRINGDATA_H
