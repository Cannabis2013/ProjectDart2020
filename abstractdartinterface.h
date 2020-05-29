#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include "idatacontext.h"
#include "iplayercontext.h"
#include <QtCore>


/*
 * This is the interface you will pass to the visual QML layer
 * Make sure that methods are marked with the Q_INVOKABLE macro and return types which are accepted by the QML engine
 *
 */

class AbstractDartInterface : public QObject
{
public:

    /*
     * Tournament:
     *  - Create/read/delete/edit tournament
     *  -
     */

    Q_INVOKABLE virtual QString createTournament(const QString &title,
                                                 const int &legCount,
                                                 const int &maxPlayers) = 0;

    Q_INVOKABLE virtual void assignPlayer(const QString &player, const QString &tournament) = 0;

    Q_INVOKABLE virtual  int tournamentsCount() = 0;
    Q_INVOKABLE virtual  QString tournamentIDFromIndex(const int &index) = 0;
    Q_INVOKABLE virtual  int tournamentMaxPlayers(const QString &id) = 0;
    Q_INVOKABLE virtual  int tournamentLegsCount(const QString &id) = 0;
    Q_INVOKABLE virtual  int tournamentPlayersCount(const QString &id) = 0;

    Q_INVOKABLE virtual int assignedPlayersCount(const QString &tournament) = 0;
    Q_INVOKABLE virtual int playersCount() = 0;
    Q_INVOKABLE virtual  QString assignedPlayerIDfromIndex(const int &tournamentID, const int &index) = 0;
    Q_INVOKABLE virtual  QString playerIDFromIndex(const int &index) = 0;

    Q_INVOKABLE virtual  int playerFirstName(const QString &player) = 0;
    Q_INVOKABLE virtual  int playerLastName(const QString &player) = 0;
    Q_INVOKABLE virtual  int playerEmail(const QString &player) = 0;

    Q_INVOKABLE virtual QString createPlayer(const QString &firstName, const QString &lastName, const QString &email) = 0;

    Q_INVOKABLE virtual  int currentGameRoundIndex(const QString &tournament) = 0;
    Q_INVOKABLE virtual  int currentGameSetIndex(const QString &tournament) = 0;

    Q_INVOKABLE virtual  void addPoint(const int& value) = 0;

    Q_INVOKABLE virtual  void startGame() = 0;
    Q_INVOKABLE virtual  void stopGame() = 0;

    Q_INVOKABLE virtual  int score(const QString &tournament, const QString &player) = 0;
};

#endif // PROJECTDARTINTERFACE_H
