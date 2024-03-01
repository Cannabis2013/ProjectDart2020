#ifndef ISTATSREPORT_H
#define ISTATSREPORT_H

class QJsonArray;

class IStatsReport {
public:
        virtual QJsonArray report() const = 0;
};

#endif // ISTATSREPORT_H
