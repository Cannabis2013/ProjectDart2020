#ifndef ISTATSREPORT_H
#define ISTATSREPORT_H

class QByteArray;

class IStatsReport {
public:
    virtual QByteArray report() const = 0;
};

#endif // ISTATSREPORT_H
