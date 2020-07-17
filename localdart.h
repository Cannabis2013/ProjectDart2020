#ifndef PROJECTDART_H
#define PROJECTDART_H

#include "abstractdartinterface.h"
#include "pointlogisticmanager.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

#define printVariable(var) #var
#define STATUS_ERROR -1;

class LocalDart : public AbstractDartInterface
{
    Q_OBJECT
    // AbstractDartInterface interface
public:
    // public types
    enum GameModes {
        FirstToPost = 0x1,
        RoundBased =0x2,
        CircularDart = 0x3
    };
    enum Status{
        ContextNotInitialized = 0x4,
        ModelNotFound = 0x5,
        NoPlayersAssigned = 0x6,
        Success = 0x7,
        UnSuccess = 0x8
    };
    enum ModelDisplayHint{HiddenHint = 0x1,DisplayHint = 0x2, allHints = 0x4};

    void createInitialModels() const override; // For testing purposes

public slots:
    void requestTournaments() override;
    void assignPlayers(const QVariantList &list, const QString &tournament) override;
    void setCurrentActiveTournament(const int &index) override;
    void requestPlayerDetails() override;
    void createPlayer(const QString &firstName, const QString &lastName, const QString &email) override;
    void createTournament(const QString &title,
                                         const int &numberOfThrows,
                                         const int &maxPlayers,
                                         const int &gameMode,
                                         const int &keyPoint) override;
    void gameModes() const override;

private slots:
    void forwardScoreFromDataContext(const QUuid &player, const int &score) override;

private :
    /*
     * Persistence related stuff
     */
    void read();
    void write();

    void initializeControllerIndexes();
    // Tournament related stuff


    int tournamentsCount() override;
    QString tournamentIDFromIndex(const int &index) override;
    int tournamentMaxPlayers(const QString &id) override;
    int tournamentLegsCount(const QString &id) override;
    int tournamentPlayersCount(const QString &id) override;
    QString tournamentTitle(const QString &id) override;
    int tournamentKeyPoint(const QString &id) override;
    int pointValue(const QString &point) const override;
    int pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) const override;
    int gameModeFromString(const QString &gameMode) const;

    /*
     * Playercontext
     */

    void assignPlayer(const QUuid &player, const QUuid &tournament) override;
    int playersCount() override;
    QString assignedPlayerIDfromIndex(const QString &tournamentID, const int &index) override;
    QString playerIDFromIndex(const int &index) override;
    QString playerFullName(const QString &player) override;
    QString playerIDFromFullName(const QString &name) override;
    QString playerFirstName(const QString &player) override;
    QString playerLastName(const QString &player) override;
    QString playerEmail(const QString &player) override;
    /*
     * Player score
     */
    /*
     * Controller context
     */
    QString resetTournament(const QString &tournament);
    QString currentActiveTournamentID() override;
    QString currentActivePlayerFullName() override;
    QString currentPlayerPoint(const int &hint = DisplayHint) override;
    int currentGameRoundIndex() override;
    int currentGameSetIndex() override;
    int currentGameLegIndex() override;
    int startGame() override;
    int stopGame() override;
    int undoTurn() override;
    int redoTurn() override;
    bool undoPossible() override;
    bool redoPossible() override;
    void handleStatusRequest() override;
    int addPoint(const int &value) override;
    int score(const QString &player) override;


    void handleGameStatusRecieved(const int &status) override;
};

#endif // PROJECTDART_H
