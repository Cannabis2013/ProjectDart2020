#ifndef STATISTICS_H
#define STATISTICS_H

#include <QJsonDocument>
#include <QJsonObject>

class Statistics {
public:
        explicit Statistics(const QString& name, double average, int low, int high, int count)
            : _name(name)
            , _average(average)
            , _low(low)
            , _high(high)
            , _throwCount(count)
        {}

        QJsonObject toJsonobject()
        {
                QJsonObject jsonObj;
                jsonObj["name"] = _name;
                jsonObj["average"] = _average;
                jsonObj["low"] = _low;
                jsonObj["high"] = _high;
                jsonObj["throwCount"] = _throwCount;
                return jsonObj;
        }

private:
        const QString _name;
        const double _average;
        const int _low;
        const int _high;
        const int _throwCount;
};

#endif // STATISTICS_H
