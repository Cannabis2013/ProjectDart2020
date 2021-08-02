#ifndef DARTSTABLEHEADERSTYLISTICS_H
#define DARTSTABLEHEADERSTYLISTICS_H

#include "itableheaderstylistics.h"
#include <qstring.h>
class DartsTableHeaderStylistics : public ITableHeaderStylistics<QString>
{
public:
    virtual int fontSize() const override
    {
        return _pointSize;
    }
    virtual void setFontSize(const int &size) override
    {
        _pointSize = size;
    }
    virtual QString fontFamily() const override
    {
        return _fontFamily;
    }
    virtual void setFontFamily(const QString &family) override
    {
        _fontFamily = family;
    }
private:
    QString _fontFamily = "MS Sans Serif";
    int _pointSize = 12;
};

#endif // DARTSTABLEHEADERSTYLISTICS_H
