#ifndef PLAYERREPORT_H
#define PLAYERREPORT_H

#include "iplayerreport.h"
#include <QObject>

class IDartsStatus;
class ServiceCollection;
class IDartsPlayers;

class PlayerReport : public QObject, public IPlayerReport {
    Q_OBJECT
public:
    PlayerReport(ServiceCollection *services);
    Q_INVOKABLE QString current() const override;
    Q_INVOKABLE bool isWinnerFound() const override;
    Q_INVOKABLE QByteArray winnerInfo() const override;
    Q_INVOKABLE QByteArray report() const override;
    Q_INVOKABLE QByteArray all() const override;

private:
    // Services
    ServiceCollection *const _services;
};

#endif // PLAYERREPORT_H
