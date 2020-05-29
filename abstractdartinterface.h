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

    virtual Q_INVOKABLE int tournamentsCount() = 0;
    virtual Q_INVOKABLE QString tournamentIDFromIndex(const int &index) = 0;
    virtual Q_INVOKABLE int tournamentMaxPlayers(const QString &id) = 0;
    virtual Q_INVOKABLE int tournamentLegsCount(const QString &id) = 0;
    virtual Q_INVOKABLE int tournamentPlayersCount(const QString &id) = 0;

    virtual Q_INVOKABLE QString assignedPlayerIDfromIndex(const int &tournamentID, const int &index) = 0;
    virtual Q_INVOKABLE QString playerIDFromIndex(const int &index) = 0;

    virtual Q_INVOKABLE int playerFirstName(const QString &player) = 0;
    virtual Q_INVOKABLE int playerLastName(const QString &player) = 0;
    virtual Q_INVOKABLE int playerEmail(const QString &player) = 0;

    virtual Q_INVOKABLE int currentGameRoundIndex(const QString &tournament) = 0;
    virtual Q_INVOKABLE int currentGameSetIndex(const QString &tournament) = 0;

    virtual Q_INVOKABLE void addPoint(const int& value) = 0;

    virtual Q_INVOKABLE void startGame() = 0;
    virtual Q_INVOKABLE void stopGame() = 0;

    virtual Q_INVOKABLE int score(const QString &tournament, const QString &player) = 0;
};

#endif // PROJECTDARTINTERFACE_H
