#ifndef ISTATUSREPORT_H
#define ISTATUSREPORT_H

class QByteArray;

class IStatusReport {
public:
        virtual QByteArray report() const = 0;
        virtual bool isWinnerFound() const = 0;
};

#endif // ISTATUSREPORT_H
