#ifndef ISTATUSREPORT_H
#define ISTATUSREPORT_H

class QJsonObject;

class IStatusReport {
public:
        virtual QJsonObject report() const = 0;
};

#endif // ISTATUSREPORT_H
