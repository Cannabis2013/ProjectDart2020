#ifndef FONTMETRICCONTEXT_H
#define FONTMETRICCONTEXT_H

#include "ifontmetriccontext.h"
#include <qfontmetrics.h>

class FontMetricContext : public IFontMetricContext<QString>
{
public:
    virtual double stringWidth(const QString &string, const QString &family, const int &pointSize) const override
    {
        auto fontMetric = QFontMetrics(QFont(family,pointSize));
        auto width = fontMetric.boundingRect(string).width();
        return width;
    }
    virtual double stringHeight(const QString &string, const QString &family, const int &pointSize) const override
    {
        auto fontMetric = QFontMetrics(QFont(family,pointSize));
        auto height = fontMetric.boundingRect(string).height();
        return height;
    }
    virtual double scale() const override
    {
        return _scale;
    }
    virtual void setScale(const double &scale) override
    {
        _scale = scale;
    }

private:
    double _scale;
};

#endif // FONTMETRICCONTEXT_H
