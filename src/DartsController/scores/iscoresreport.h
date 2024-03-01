#ifndef ISCORESREPORT_H
#define ISCORESREPORT_H

class QJsonObject;

class IScoresReport {
public:
        virtual QJsonObject report() const = 0;
};

#endif // ISCORESREPORT_H
