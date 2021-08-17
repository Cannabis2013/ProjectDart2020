#include "mhtablesectionmetrics.h"

int MHTableSectionMetrics::width(const QVariantList &data, const QString &pFamily, const int &pSize,
                         const QString &sFamily, const int &sSize) const
{
    GreatestWidth gw;
    return gw.greatestWidth(data,GreatestWidth::FontConfig(pFamily,pSize),
                                 GreatestWidth::FontConfig(sFamily,sSize),scale());
}

int MHTableSectionMetrics::width(const QString &string, const QString &hFamily, const int &hSize) const
{
    GreatestWidth gw;
    return gw.greatestWidth(string,GreatestWidth::FontConfig(hFamily,hSize),scale());
}

int MHTableSectionMetrics::height(const QVariantList &data, const QString &pFamily, const int &pSize, const QString &sFamily, const int &sSize) const
{
    GreatestHeight gh;
    return gh.greatestHeight(data,GreatestHeight::FontConfig(pFamily,pSize),
                                  GreatestHeight::FontConfig(sFamily,sSize),scale());
}

int MHTableSectionMetrics::height(const QString &string, const QString &hFamily, const int &hSize) const
{
    GreatestHeight gh;
    return gh.greatestHeight(string,GreatestHeight::FontConfig(hFamily,hSize),scale());
}

double MHTableSectionMetrics::scale() const
{
    return _scale;
}

void MHTableSectionMetrics::setScale(double newScale)
{
    _scale = newScale;
    emit scaleChanged();
}
