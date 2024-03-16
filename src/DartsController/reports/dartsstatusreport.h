#ifndef DARTSSTATUSREPORT_H
#define DARTSSTATUSREPORT_H

#include "istatusreport.h"

#include <QObject>

class ServiceCollection;
class IDartsStatus;
class IDartsPlayers;
class IDartsIndexes;
class QJsonObject;

class DartsStatusReport : public QObject, public IStatusReport {
        Q_OBJECT
public:
        DartsStatusReport(ServiceCollection* services);

        Q_INVOKABLE QByteArray report() const override;
        Q_INVOKABLE bool isWinnerFound() const override;

private:
        // Services
        IDartsPlayers* const _players;
        IDartsStatus* const _status;
};

#endif // DARTSSTATUSREPORT_H
