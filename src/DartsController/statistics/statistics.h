#ifndef STATISTICS_H
#define STATISTICS_H

#include <QJsonObject>

class Statistics {
public:
        explicit Statistics(const QString& name, double average, int low, int high)
            : _name(name)
            , _average(average)
            , _low(low)
            , _high(high)
        {}

        QJsonObject toJsonobject()
        {
                QJsonObject jsonObj;
                jsonObj["playerName"] = _name;
                jsonObj["average"] = _average;
                jsonObj["low"] = _low;
                jsonObj["high"] = _high;
                return jsonObj;
        }

private:
        const QString _name;
        const double _average;
        const int _low;
        const int _high;
};

#endif // STATISTICS_H
