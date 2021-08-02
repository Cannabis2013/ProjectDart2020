#ifndef DARTSPOINTCELLSTYLISTICS_H
#define DARTSPOINTCELLSTYLISTICS_H

#include "itablecellstylistics.h"
class DartsPointCellStylistics : public ITableCellStylistics<QString>
{
public:
    virtual QString scoreFontFamily() const
    {
        return _scoreFontFamily;
    }
    virtual QString pointFontFamily() const
    {
        return _pointFontFamily;
    }
    virtual int scoreFontSize() const
    {
        return _scoreFontSize;
    }
    virtual int pointFontSize() const
    {
        return _pointFontSize;
    }
private:
    QString _scoreFontFamily = "MS Sans Serif";
    QString _pointFontFamily = "MS Sans Serif";
    int _scoreFontSize = 12;
    int _pointFontSize = 8;
};

#endif // DEFAULTFONTCONTEXT_H
