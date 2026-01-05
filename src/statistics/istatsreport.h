#ifndef ISTATSREPORT_H
#define ISTATSREPORT_H

class QByteArray;

class IStatsReport {
public:
    virtual QByteArray all() const = 0;
    virtual QByteArray current() const = 0;
    virtual QByteArray player(const int& index) const = 0;
};

#endif // ISTATSREPORT_H
