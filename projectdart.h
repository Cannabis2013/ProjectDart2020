#ifndef PROJECTDART_H
#define PROJECTDART_H

#include "idatacontext.h"
#include "igamecontroller.h"
#include "abstractdartinterface.h"
#include "ipointlogisticmanager.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

typedef IDataContext<QUuid, QList<QUuid>,QString> DefaultDataContext;
typedef IGameController<QUuid,QString, DefaultDataContext> DefaultGameController;

class ProjectDart : public AbstractDartInterface
{

    // AbstractDartInterface interface
public:

    // public types

    enum gameModes {
        decrementingDart,
        targetDart
    };

    // Tournament related stuff
    Q_INVOKABLE QString createTournament(const QString &title,
                             const int &legCount,
                             const int &maxPlayers,
                             const int &gameMode) override;

    Q_INVOKABLE int tournamentsCount() override;
    Q_INVOKABLE QString tournamentIDFromIndex(const int &index) override;
    Q_INVOKABLE int tournamentMaxPlayers(const QString &id) override;
    Q_INVOKABLE int tournamentLegsCount(const QString &id) override;
    Q_INVOKABLE int tournamentPlayersCount(const QString &id) override;

    Q_INVOKABLE QStringList gameModes() const override;

    // Player related stuff
    Q_INVOKABLE QString createPlayer(const QString &firstName, const QString &lastName, const QString &email) override;
    Q_INVOKABLE void assignPlayer(const QString &player, const QString &tournament) override;
    Q_INVOKABLE int assignedPlayersCount(const QString &tournament) override;
    Q_INVOKABLE int playersCount() override;
    Q_INVOKABLE QString assignedPlayerIDfromIndex(const int &tournamentID, const int &index) override;
    Q_INVOKABLE QString playerIDFromIndex(const int &index) override;
    Q_INVOKABLE int playerFirstName(const QString &player) override;
    Q_INVOKABLE int playerLastName(const QString &player) override;
    Q_INVOKABLE int playerEmail(const QString &player) override;

    Q_INVOKABLE int currentGameRoundIndex(const QString &tournament) override;
    Q_INVOKABLE int currentGameSetIndex(const QString &tournament) override;

    Q_INVOKABLE void startGame() override;
    Q_INVOKABLE void stopGame() override;

    Q_INVOKABLE void addPoint(const int &value) override;

    Q_INVOKABLE int score(const QString &tournament, const QString &player) override;

};

#endif // PROJECTDART_H
