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
    Q_OBJECT
public:

    /*
     * Tournament:
     *  - Create/read/delete/edit tournament
     *  -
     */

    Q_INVOKABLE virtual QString createTournament(const QString &title,
                                     const int &legCount,
                                     const int &maxPlayers,
                                     const int &gameMode,
                                     const int &keyPoint) = 0;

    Q_INVOKABLE virtual void assignPlayer(const QString &player, const QString &tournament) = 0;
    Q_INVOKABLE virtual int tournamentsCount() = 0;
    Q_INVOKABLE virtual QString tournamentIDFromIndex(const int &index) = 0;
    Q_INVOKABLE virtual int tournamentMaxPlayers(const QString &id) = 0;
    Q_INVOKABLE virtual int tournamentLegsCount(const QString &id) = 0;
    Q_INVOKABLE virtual int tournamentPlayersCount(const QString &id) = 0;
    Q_INVOKABLE virtual QString tournamentTitle(const QString &id) = 0;
    Q_INVOKABLE virtual int tournamentKeyPoint(const QString &id) = 0;
    Q_INVOKABLE virtual int pointValue(const QString &point) const = 0;
    Q_INVOKABLE virtual int pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) const = 0;
    Q_INVOKABLE virtual QStringList gameModes() const = 0;
    Q_INVOKABLE virtual int playersCount() = 0;
    Q_INVOKABLE virtual QString assignedPlayerIDfromIndex(const QString &tournamentID, const int &index) = 0;
    Q_INVOKABLE virtual QString playerIDFromIndex(const int &index) = 0;
    Q_INVOKABLE virtual QString playerIDFromFullName(const QString &name) = 0;
    Q_INVOKABLE virtual QString playerFullName(const QString &player) = 0;
    Q_INVOKABLE virtual QString playerFirstName(const QString &player) = 0;
    Q_INVOKABLE virtual QString playerLastName(const QString &player) = 0;
    Q_INVOKABLE virtual QString playerEmail(const QString &player) = 0;
    Q_INVOKABLE virtual QString createPlayer(const QString &firstName, const QString &lastName, const QString &email) = 0;
    Q_INVOKABLE virtual QString currentActiveTournamentID() = 0;
    Q_INVOKABLE virtual int setCurrentActiveTournament(const int &index) = 0;
    Q_INVOKABLE virtual QString currentActivePlayerFullName() = 0;
    Q_INVOKABLE virtual QString currentPlayerPoint(const int &hint) = 0;
    Q_INVOKABLE virtual int currentGameRoundIndex() = 0;
    Q_INVOKABLE virtual int currentGameSetIndex() = 0;
    Q_INVOKABLE virtual int currentGameLegIndex() = 0;
    Q_INVOKABLE virtual int addPoint(const int& value) = 0;
    Q_INVOKABLE virtual int startGame() = 0;
    Q_INVOKABLE virtual int stopGame() = 0;
    Q_INVOKABLE virtual int undoTurn() = 0;
    Q_INVOKABLE virtual int redoTurn() = 0;
    Q_INVOKABLE virtual bool undoPossible() = 0;
    Q_INVOKABLE virtual bool redoPossible() = 0;
    Q_INVOKABLE virtual int gameStatus() = 0;
    Q_INVOKABLE virtual int score(const QString &player) = 0;
    Q_INVOKABLE virtual void requestScoreBoardUpdate() = 0;
    Q_INVOKABLE virtual void requestTournaments() = 0;

signals:
    void sendStatus(const int &status);
    void sendPlayerScore(const QString &playerName, const int &score);
    void sendAssignedPlayerName(const QString &playerName);
    void sendRequestetTournament(const QString &title,
                                 const int &numberOfThrows,
                                 const int &maxPlayers,
                                 const int &gameMode,
                                 const int &keyPoint,
                                 const int &playersCount);
    void sendCurrentTournamentKeyPoint(const int &point);
    void sendInformalControllerValues(const int &roundIndex, const QString &playerName, const bool &undoAvailable, const bool &redoAvailable);

};

#endif // PROJECTDARTINTERFACE_H
