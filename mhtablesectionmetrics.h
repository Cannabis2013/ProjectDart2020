#ifndef MHTABLESECTIONMETRICS_H
#define MHTABLESECTIONMETRICS_H

#include <qobject.h>
#include "greatestwidth.h"
#include "greatestheight.h"

class MHTableSectionMetrics : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_INVOKABLE int width(const QVariantList &data,
                          const QString &pFamily, const int &pSize,
                          const QString &sFamily, const int &sSize) const;
    Q_INVOKABLE int width(const QString &string, const QString &hFamily, const int &hSize) const;
    Q_INVOKABLE int height(const QVariantList &data,
                          const QString &pFamily, const int &pSize,
                          const QString &sFamily, const int &sSize) const;
    Q_INVOKABLE int height(const QString &string, const QString &hFamily, const int &hSize) const;
signals:
    void scaleChanged();
private:
    double scale() const;
    void setScale(double newScale);
    double _scale;
};
#endif // DARTSTABLEFONTMETRICS_H
