#include "fontmetrics.h"

#include <QFontMetrics>

FontMetrics::FontMetrics(const QString& fontFamily)
    : _family(fontFamily)
{
}

double FontMetrics::width(const QString& str, const int& size, const int& weight) const
{
        auto rect = fontRect(str, size, weight);
        return rect.width();
}

double FontMetrics::height(const QString& str, const int& size, const int& weight) const
{
        auto rect = fontRect(str, size, weight);
        return rect.height();
}

QRect FontMetrics::fontRect(const QString& str, const int& size, const int& weight) const
{
        QFont font(_family, size, weight);
        QFontMetrics metrics(font);
        return metrics.boundingRect(str);
}
