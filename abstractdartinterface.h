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

    virtual QString createTournament(const QString &title,
                                     const int &legCount,
                                     const int &maxPlayers,
                                     const int &gameMode,
                                     const int &keyPoint) = 0;

    virtual void assignPlayer(const QString &player, const QString &tournament) = 0;

    virtual  int tournamentsCount() = 0;
    virtual  QString tournamentIDFromIndex(const int &index) = 0;
    virtual  int tournamentMaxPlayers(const QString &id) = 0;
    virtual  int tournamentLegsCount(const QString &id) = 0;
    virtual  int tournamentPlayersCount(const QString &id) = 0;

    virtual QStringList gameModes() const = 0;

    virtual int playersCount() = 0;
    virtual  QString assignedPlayerIDfromIndex(const QString &tournamentID, const int &index) = 0;
    virtual  QString playerIDFromIndex(const int &index) = 0;

    virtual  QString playerFirstName(const QString &player) = 0;
    virtual  QString playerLastName(const QString &player) = 0;
    virtual  QString playerEmail(const QString &player) = 0;

    virtual QString createPlayer(const QString &firstName, const QString &lastName, const QString &email) = 0;

    virtual  int currentGameRoundIndex() = 0;
    virtual  int currentGameSetIndex() = 0;

    virtual  void addPoint(const int& value) = 0;

    virtual  void startGame() = 0;
    virtual  void stopGame() = 0;

    virtual  int score(const QString &tournament, const QString &player) = 0;

};

#endif // PROJECTDARTINTERFACE_H
