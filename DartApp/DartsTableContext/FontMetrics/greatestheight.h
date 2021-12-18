#ifndef GREATESTHEIGHT_H
#define GREATESTHEIGHT_H

#include <qfontmetrics.h>
#include <QVariantList>

class GreatestHeight
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
    int greatestHeight(const QVariantList &data, const FontConfig &pConf, const FontConfig &sConf)
    {
        return calcHeight(data,pConf,sConf);

    }
    int greatestHeight(const QString &string, const FontConfig &hConf)
    {
        return calcHeight(string,hConf);
    }
private:
    int combinedHeight(const QVariantMap &map, const FontConfig &pConf, const FontConfig &sConf)
    {
        auto p = createPair(map);
        auto pw = calcHeight(p.first,pConf);
        auto sw = calcHeight(p.second,sConf);
        auto sum = pw + sw;
        return sum;
    }
    QPair<QString,QString> createPair(const QVariantMap &map)
    {
        auto p = map.value("point").toInt();
        auto s = map.value("score").toInt();
        return QPair<QString,QString>(QString::number(p),QString::number(s));
    }
    int calcHeight(const QVariantList &data, const FontConfig &pConf, const FontConfig &sConf)
    {
        int t = 0;
        for (const auto &d : data)
        {
            auto sum = combinedHeight(d.toMap(),pConf,sConf);
            t = findGreatest(t,sum);
        }
        return t;
    }
    int calcHeight(const QString &string, const FontConfig &fontConf)
    {
        auto f = QFont(fontConf.family(),fontConf.pointSize());
        auto m = QFontMetrics(f);
        return m.boundingRect(string).height();
    }
    int findGreatest(const int &x, const int &y) const
    {
        return y > x ? y : x;
    }
};


#endif // GREATESTHEIGHT_H
