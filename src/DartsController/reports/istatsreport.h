#ifndef ISTATSREPORT_H
#define ISTATSREPORT_H

class QByteArray;

class IStatsReport {
public:
        virtual QByteArray playerOne() const = 0;
        virtual QByteArray playerTwo() const = 0;
};

#endif // ISTATSREPORT_H
