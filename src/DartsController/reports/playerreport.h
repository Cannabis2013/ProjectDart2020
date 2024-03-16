#ifndef PLAYERREPORT_H
#define PLAYERREPORT_H

#include "src/DartsController/reports/iplayerreport.h"
#include <QObject>

class ServiceCollection;
class IDartsPlayers;

class PlayerReport : public QObject, public IPlayerReport {
        Q_OBJECT
public:
        PlayerReport(ServiceCollection* services);

        Q_INVOKABLE QByteArray report() const override;
        Q_INVOKABLE QByteArray playerOne() const override;
        Q_INVOKABLE QByteArray playerTwo() const override;

private:
        // Services
        IDartsPlayers* _players;
};

#endif // PLAYERREPORT_H
