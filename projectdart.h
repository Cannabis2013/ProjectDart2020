#ifndef PROJECTDART_H
#define PROJECTDART_H

#include "localstandarddart.h"
#include "abstractdartinterface.h"
#include "ipointlogisticmanager.h"
#include "localplayercontext.h"
#include "localplayerbuilder.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

typedef IPlayerContext<QUuid,QList<QUuid>,QString, DefaultPlayerBuilder> PlayerContextInterface;
typedef IDataContext<QUuid, QList<QUuid>,QString,ITournamentBuilder> DataContextInterface;
typedef IGameController<QUuid,QString, DataContextInterface> GameControllerInterface;

#define printVariable(var) #var

class ProjectDart : public AbstractDartInterface
{
    Q_OBJECT
    // AbstractDartInterface interface
public:
    ProjectDart();

    // public types
    enum gameModes {
        FirstToPost,
        RoundBased,
        CircularDart
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

    Q_INVOKABLE int pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) override;

    Q_INVOKABLE QStringList gameModes() const override;
    Q_INVOKABLE int gameModeFromString(const QString &gameMode) const;

    // Player related stuff
    Q_INVOKABLE QString createPlayer(const QString &firstName, const QString &lastName, const QString &email) override;
    Q_INVOKABLE void assignPlayer(const QString &player, const QString &tournament) override;
    Q_INVOKABLE int playersCount() override;
    Q_INVOKABLE QString assignedPlayerIDfromIndex(const QString &tournamentID, const int &index) override;
    Q_INVOKABLE QString playerIDFromIndex(const int &index) override;
    Q_INVOKABLE QString playerFirstName(const QString &player) override;
    Q_INVOKABLE QString playerLastName(const QString &player) override;
    Q_INVOKABLE QString playerEmail(const QString &player) override;

    Q_INVOKABLE int currentGameRoundIndex() override;
    Q_INVOKABLE int currentGameSetIndex() override;

    Q_INVOKABLE void startGame() override;
    Q_INVOKABLE void stopGame() override;

    Q_INVOKABLE int addPoint(const int &value) override;

    Q_INVOKABLE int score(const QString &tournament, const QString &player) override;

private:
    DataContextInterface *_dataContext;
    PlayerContextInterface *_playerContext;
    GameControllerInterface *_gameController;

};

#endif // PROJECTDART_H
