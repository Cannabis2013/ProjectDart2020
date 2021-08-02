#ifndef ITABLEHEADERSTYLISTICS_H
#define ITABLEHEADERSTYLISTICS_H

template<typename TString>
class ITableHeaderStylistics
{
public:
    virtual int fontSize() const = 0;
    virtual void setFontSize(const int &size) = 0;
    virtual TString fontFamily() const = 0;
    virtual void setFontFamily(const TString &family) = 0;
};
#endif // ITABLEHEADERSTYLISTICS_H
