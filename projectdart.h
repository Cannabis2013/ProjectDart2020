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
    QString createTournament(const QString &title, const int &legCount, const int &maxPlayers) override;
    int tournamentsCount() override;
    QString tournamentIDFromIndex(const int &index) override;
    int tournamentMaxPlayers(const QString &id) override;
    int tournamentLegsCount(const QString &id) override;
    QString createPlayer(const QString &firstName, const QString &lastName, const QString &email) override;
    int tournamentPlayersCount(const QString &id) override;

    void assignPlayer(const QString &player, const QString &tournament) override;
    int assignedPlayersCount(const QString &tournament) override;
    int playersCount() override;
    QString assignedPlayerIDfromIndex(const int &tournamentID, const int &index) override;
    QString playerIDFromIndex(const int &index) override;
    int playerFirstName(const QString &player) override;
    int playerLastName(const QString &player) override;
    int playerEmail(const QString &player) override;

    int currentGameRoundIndex(const QString &tournament) override;
    int currentGameSetIndex(const QString &tournament) override;

    void startGame() override;
    void stopGame() override;

    void addPoint(const int &value) override;

    int score(const QString &tournament, const QString &player) override;

    // AbstractDartInterface interface
public:
};

#endif // PROJECTDART_H
