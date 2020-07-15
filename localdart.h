#ifndef PROJECTDART_H
#define PROJECTDART_H

#include "localfirsttopost.h"
#include "abstractdartinterface.h"
#include "pointlogisticmanager.h"
#include "localplayercontext.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

typedef IPlayerContext<QUuid,QList<QUuid>,QString, DefaultPlayerBuilder> PlayerContextInterface;
typedef IDataContext<QUuid, QList<QUuid>,QString,ITournamentBuilder> DataContextInterface;
typedef IGameController<QUuid,QString, DataContextInterface> GameControllerInterface;

#define printVariable(var) #var
#define STATUS_ERROR -1;

class LocalDart : public AbstractDartInterface
{
    Q_OBJECT
    // AbstractDartInterface interface
public:
    LocalDart();

    // public types
    enum GameModes {
        FirstToPost = 0x1,
        RoundBased =0x2,
        CircularDart = 0x3
    };
    enum Status{
        ContextNotInitialized = 0x4,
        GameStartet = 0x5,
        GameStopped = 0x6,
        GameReady = 0x7,
        ModelNotFound = 0x8,
        NoPlayersAssigned = 0x9,
        Success = 0xa,
        UnSuccess = 0xb
    };

    void read();
    void write();

    // Tournament related stuff
    Q_INVOKABLE QString createTournament(const QString &title,
                                         const int &legCount,
                                         const int &maxPlayers,
                                         const int &gameMode,
                                         const int &keyPoint) override;

    Q_INVOKABLE int tournamentsCount() override;
    Q_INVOKABLE QString tournamentIDFromIndex(const int &index) override;
    Q_INVOKABLE int tournamentMaxPlayers(const QString &id) override;
    Q_INVOKABLE int tournamentLegsCount(const QString &id) override;
    Q_INVOKABLE int tournamentPlayersCount(const QString &id) override;
    Q_INVOKABLE QString tournamentTitle(const QString &id) override;
    Q_INVOKABLE int tournamentKeyPoint(const QString &id) override;
    Q_INVOKABLE int pointValue(const QString &point) const override;
    Q_INVOKABLE int pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) const override;
    Q_INVOKABLE QStringList gameModes() const override;
    Q_INVOKABLE int gameModeFromString(const QString &gameMode) const;

    /*
     * Playercontext
     */
    Q_INVOKABLE QString createPlayer(const QString &firstName, const QString &lastName, const QString &email) override;
    Q_INVOKABLE void assignPlayer(const QString &player, const QString &tournament) override;
    Q_INVOKABLE int playersCount() override;
    Q_INVOKABLE QString assignedPlayerIDfromIndex(const QString &tournamentID, const int &index) override;
    Q_INVOKABLE QString playerIDFromIndex(const int &index) override;
    Q_INVOKABLE QString playerFullName(const QString &player) override;
    Q_INVOKABLE QString playerIDFromFullName(const QString &name) override;
    Q_INVOKABLE QString playerFirstName(const QString &player) override;
    Q_INVOKABLE QString playerLastName(const QString &player) override;
    Q_INVOKABLE QString playerEmail(const QString &player) override;
    /*
     * Player score
     */
    /*
     * Controller context
     */
    Q_INVOKABLE QString resetTournament(const QString &tournament);
    Q_INVOKABLE QString currentActiveTournamentID() override;
    Q_INVOKABLE int setCurrentActiveTournament(const int &index) override;
    Q_INVOKABLE QString currentActivePlayerFullName() override;
    Q_INVOKABLE QString currentPlayerPoint(const int &hint = LocalDataContext::DisplayHint) override;
    Q_INVOKABLE int currentGameRoundIndex() override;
    Q_INVOKABLE int currentGameSetIndex() override;
    Q_INVOKABLE int currentGameLegIndex() override;
    Q_INVOKABLE int startGame() override;
    Q_INVOKABLE int stopGame() override;
    Q_INVOKABLE int undoTurn() override;
    Q_INVOKABLE int redoTurn() override;
    Q_INVOKABLE bool undoPossible() override;
    Q_INVOKABLE bool redoPossible() override;
    Q_INVOKABLE int gameStatus() override;
    Q_INVOKABLE int addPoint(const int &value) override;
    Q_INVOKABLE int score(const QString &player) override;
    Q_INVOKABLE void requestCurrentTournamentPlayerScores() override;
    Q_INVOKABLE void requestTournaments() override;

private:
    void createInitialModels(); // For testing purposes

    DataContextInterface *_dataContext = nullptr;
    PlayerContextInterface *_playerContext= nullptr;
    GameControllerInterface *_gameController= nullptr;

};

#endif // PROJECTDART_H
