#ifndef GREATESTWIDTH_H
#define GREATESTWIDTH_H

#include <qfontmetrics.h>
#include <QVariantList>

class GreatestWidth
{
public:
    class FontConfig
    {
    public:
        FontConfig(const QString &family, const int &pointSize): _family(family), _pointSize(pointSize){}
        int pointSize() const
        {
            return _pointSize;
        }
        const QString &family() const
        {
            return _family;
        }
    private:
        QString _family;
        int _pointSize;
    };
    int greatestWidth(const QVariantList &data, const FontConfig &pConf, const FontConfig &sConf)
    {
        return calcWidth(data,pConf,sConf);

    }
    int greatestWidth(const QVariantList &data, const FontConfig &conf)
    {
        return calcWidth(data,conf);

    }
    int greatestWidth(const QString &string, const FontConfig &hConf)
    {
        return calcWidth(string,hConf);
    }
private:
    int combinedWidth(const QVariantMap &map, const FontConfig &pConf, const FontConfig &sConf)
    {
        auto p = createPair(map);
        auto pw = calcWidth(p.first,pConf);
        auto sw = calcWidth(p.second,sConf);
        auto sum = pw + sw;
        return sum;
    }
    QPair<QString,QString> createPair(const QVariantMap &map)
    {
        auto p = map.value("point").toInt();
        auto s = map.value("score").toInt();
        return QPair<QString,QString>(QString::number(p),QString::number(s));
    }
    int calcWidth(const QVariantList &data, const FontConfig &pConf, const FontConfig &sConf)
    {
        int t = 0;
        for (const auto &d : data)
        {
            auto sum = combinedWidth(d.toMap(),pConf,sConf);
            t = findGreatest(t,sum);
        }
        return t;
    }
    int calcWidth(const QVariantList &data, const FontConfig &conf)
    {
        int t = 0;
        for (const auto &d : data)
        {
            auto map = d.toMap();
            auto mapValue = map.value("score");
            auto sum = calcWidth(mapValue.toString(),conf);
            t = findGreatest(t,sum);
        }
        return t;
    }
    int findGreatest(const int &x, const int &y) const
    {
        return y > x ? y : x;
    }
    int calcWidth(const QString &string, const FontConfig &fontConf)
    {
        auto f = QFont(fontConf.family(),fontConf.pointSize());
        auto m = QFontMetrics(f);
        return m.boundingRect(string).width();
    }
};
#endif // GREATESTWIDTH_H
