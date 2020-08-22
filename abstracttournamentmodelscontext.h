#ifndef ABSTRACTTOURNAMENTMODELSCONTEXT_H
#define ABSTRACTTOURNAMENTMODELSCONTEXT_H

#include "idatacontext.h"
#include "modelbuildercontext.h"
#include "idatamodelbuilder.h"
#include <qobject.h>

typedef QList<QPair<QUuid,QString>> PlayerPairs;

class AbstractTournamentModelsContext : public QObject
{
    Q_OBJECT

public slots:
    virtual void handleCreateTournament(const QString &title,
                                   const int &keyPoint,
                                   const int &throws,
                                   const int &gameMode,
                                   const int &winCondition) = 0;
    virtual void handleAssignPlayers(const QUuid &tournament, const QList<QUuid> &playersID) = 0;
    virtual void handleDeleteTournaments(const QVector<int>&indexes) = 0;
    virtual void handleTransmitPlayerScores(const QUuid &tournament,
                                            const QList<QPair<QUuid, QString> > &players) = 0;
    virtual void handleGetAssignedPlayersToTournament(const QUuid &tournament) = 0;
    virtual void handleTransmitTournaments() = 0;
    virtual void handleAssembleTournamentMeta(const QUuid &tournament) = 0;
    virtual void handleTournamentIDFromIndex(const int &index) = 0;
    virtual void handleRequestForTournamentDetails(const QUuid &tournament, const PlayerPairs &playerNames) = 0;
    virtual void handleRequestTournamentIndexes(const QUuid &tournament) = 0;
    virtual void addScore(const QUuid &tournament,
                                    const QUuid &playerID,
                                    const int &roundIndex,
                                    const int &setIndex,
                                    const int &throwIndex,
                                    const int &point,
                                    const int &score) = 0;
signals:
    void confirmPlayersAssignment(const bool &status);
    void confirmTournamentCreated(const bool &status, const QUuid &tournament);
    void confirmTournamentsDeleted(const bool &status);
    void sendPlayerScore(const QString &player, const int &point, const int &score);
    void sendAssignedPlayers(const QList<QUuid> &players);
    void confirmScoresTransmittedAndContextUpdated();
    void sendTournament(const QString &title,
                        const int &numberOfThrows,
                        const int &gameMode,
                        const int &keyPoint,
                        const int &playersCount);
    void sendTournamentMeta(const QString &title,
                            const int &gameMode,
                            const int &keyPoint,
                            const QList<QUuid> &assignedPlayers);
    void sendTournamentIDFromIndex(const QUuid &tournament, const QList<QUuid> &assignedPlayersID);
    void sendTournamentDetails(const QUuid &tournament,
                               const int &keyPoint,
                               const int &terminalKeyCode,
                               const int &numberOfThrows,
                               const PlayerPairs &assignedPlayerPairs);
    void sendTournamentIndexes(const int &roundIndex,
                               const int &setIndex,
                               const int &throwIndex,
                               const int &turnIndex,
                               const int &totalTurns ,
                               const QList<int> &playerScores);
};

#endif // ABSTRACTTOURNAMENTMODELSCONTEXT_H

