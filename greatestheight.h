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
    int greatestHeight(const QVariantList &data, const FontConfig &pConf, const FontConfig &sConf,const int &scale)
    {
        return calcHeight(data,pConf,sConf,scale);

    }
    int greatestHeight(const QString &string, const FontConfig &hConf, const int &scale)
    {
        return calcHeight(string,hConf,scale);
    }
private:
    int combinedHeight(const QVariantMap &map, const FontConfig &pConf, const FontConfig &sConf,const int &scale)
    {
        auto p = createPair(map);
        auto pw = calcHeight(p.first,pConf,scale);
        auto sw = calcHeight(p.second,sConf,scale);
        auto sum = pw + sw;
        return sum;
    }
    QPair<QString,QString> createPair(const QVariantMap &map)
    {
        auto p = map.value("point").toInt();
        auto s = map.value("score").toInt();
        return QPair<QString,QString>(QString::number(p),QString::number(s));
    }
    int calcHeight(const QVariantList &data, const FontConfig &pConf, const FontConfig &sConf, const int &scale)
    {
        int t = 0;
        for (const auto &d : data)
        {
            auto sum = combinedHeight(d.toMap(),pConf,sConf,scale);
            t = findGreatest(t,sum);
        }
        return t;
    }
    int calcHeight(const QString &string, const FontConfig &fontConf, const int &scale)
    {
        auto f = QFont(fontConf.family(),fontConf.pointSize());
        auto m = QFontMetrics(f);
        auto w = m.boundingRect(string).height();
        return w*scale;
    }
    int findGreatest(const int &x, const int &y) const
    {
        return y > x ? y : x;
    }
};


#endif // GREATESTHEIGHT_H
