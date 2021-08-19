#ifndef MHTABLESECTIONMETRICS_H
#define MHTABLESECTIONMETRICS_H

#include <qobject.h>
#include "greatestwidth.h"
#include "greatestheight.h"

class MHTableSectionMetrics : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE int width(const QVariantList &data,
                          const QString &pFamily, const int &pSize,
                          const QString &sFamily, const int &sSize) const
    {
        GreatestWidth gw;
        return gw.greatestWidth(data,GreatestWidth::FontConfig(pFamily,pSize),
                                GreatestWidth::FontConfig(sFamily,sSize));
    }
    Q_INVOKABLE int width(const QString &string, const QString &hFamily, const int &hSize) const
    {
        GreatestWidth gw;
        return gw.greatestWidth(string,GreatestWidth::FontConfig(hFamily,hSize));
    }
    Q_INVOKABLE int height(const QVariantList &data,
                           const QString &pFamily, const int &pSize,
                           const QString &sFamily, const int &sSize) const
    {
        GreatestHeight gh;
        return gh.greatestHeight(data,GreatestHeight::FontConfig(pFamily,pSize),
                                 GreatestHeight::FontConfig(sFamily,sSize));
    }
    Q_INVOKABLE int height(const QString &string, const QString &hFamily, const int &hSize) const
    {
        GreatestHeight gh;
        return gh.greatestHeight(string,GreatestHeight::FontConfig(hFamily,hSize));
    }
};
#endif // DARTSTABLEFONTMETRICS_H
