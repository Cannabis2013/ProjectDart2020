#ifndef ITABLECELLFONTSTYLISTICS_H
#define ITABLECELLFONTSTYLISTICS_H

#include <qstring.h>

template<typename TString>
class ITableCellStylistics
{
public:
    virtual TString scoreFontFamily() const = 0;
    virtual TString pointFontFamily() const = 0;
    virtual int scoreFontSize() const = 0;
    virtual int pointFontSize() const  = 0;
};

#endif // IDATAMODELFONTSSTYLISTICS_H
