#ifndef FONTMETRICS_H
#define FONTMETRICS_H

#include "ifontmetrics.h"
#include <QObject>
#include <QString>

class FontMetrics : public QObject, public IFontMetrics {
        Q_OBJECT
public:
        FontMetrics(const QString& fontFamily);

        Q_INVOKABLE double width(const QString& str, const int& size, const int& weight) const override;
        Q_INVOKABLE double height(const QString& str, const int& size, const int& weight) const override;

private:
        QRect fontRect(const QString& str, const int& size, const int& weight) const;

        const QString _family;
};

#endif // FONTMETRICS_H
