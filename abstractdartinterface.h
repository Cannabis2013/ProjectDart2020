#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

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
    virtual int tournamentsCount() = 0;
    virtual QString tournamentIDFromIndex(const int &index) = 0;
    virtual int tournamentMaxPlayers(const QString &id) = 0;
    virtual int tournamentLegsCount(const QString &id) = 0;
    virtual int tournamentPlayersCount(const QString &id) = 0;
    virtual QString tournamentTitle(const QString &id) = 0;
    virtual int tournamentKeyPoint(const QString &id) = 0;
    virtual int tournamentRoundsCount(const QString &tournament) = 0;
    virtual int pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) = 0;
    virtual QString playerPoint(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) = 0;
    virtual QStringList gameModes() const = 0;
    virtual int playersCount() = 0;
    virtual QString assignedPlayerIDfromIndex(const QString &tournamentID, const int &index) = 0;
    virtual QString playerIDFromIndex(const int &index) = 0;
    virtual QString playerIDFromFullName(const QString &name) = 0;
    virtual QString playerFullName(const QString &player) = 0;
    virtual QString playerFirstName(const QString &player) = 0;
    virtual QString playerLastName(const QString &player) = 0;
    virtual QString playerEmail(const QString &player) = 0;
    virtual QString createPlayer(const QString &firstName, const QString &lastName, const QString &email) = 0;
    virtual QString currentActiveTournamentID() = 0;
    virtual int setCurrentActiveTournament(const QString &id) = 0;
    virtual QString currentActivePlayerFullName() = 0;
    virtual QString currentPlayerPoint() = 0;
    virtual int currentGameRoundIndex() = 0;
    virtual int currentGameSetIndex() = 0;
    virtual int currentGameLegIndex() = 0;
    virtual int addPoint(const int& value) = 0;
    virtual int startGame() = 0;
    virtual int stopGame() = 0;
    virtual int undoTurn() = 0;
    virtual int redoTurn() = 0;
    virtual bool undoPossible() = 0;
    virtual bool redoPossible() = 0;
    virtual int gameStatus() = 0;
    virtual int score(const QString &player) = 0;

};

#endif // PROJECTDARTINTERFACE_H
