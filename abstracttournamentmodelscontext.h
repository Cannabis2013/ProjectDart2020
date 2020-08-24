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
    virtual void assembleAndAddTournament(const QString &title,
                                   const int &keyPoint,
                                   const int &throws,
                                   const int &gameMode,
                                   const int &winCondition, const QList<QUuid> &assignedPlayersID) = 0;
    virtual void handleAssignPlayers(const QUuid &tournament, const QList<QUuid> &playersID) = 0;
    virtual void deleteTournament(const QVector<int>&indexes) = 0;
    virtual void handleTransmitPlayerScores(const QUuid &tournament,
                                            const QList<QPair<QUuid, QString> > &players) = 0;
    virtual void handleGetAssignedPlayersToTournament(const QUuid &tournament) = 0;
    virtual void handleTransmitTournaments() = 0;
    virtual void handleRequestForTournamentMetaData(const QUuid &tournament) = 0;
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
    virtual void handleRequestUpdateContext(const QUuid &tournamentID,
                                            const int &roundIndex,
                                            const int &setIndex) = 0;
signals:
    void transmitResponse(const int &status, const QVariantList &arguments);
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
                               const int &gameMode,
                               const PlayerPairs &assignedPlayerPairs);
    void sendTournamentIndexes(const int &roundIndex,
                               const int &setIndex,
                               const int &throwIndex,
                               const int &turnIndex,
                               const int &totalTurns ,
                               const QList<int> &playerScores);
    void confirmScoresAddedToContext(const QUuid &playerID,
                                     const int &point,
                                     const int &score);
    void confirmContextUpdated();
};

#endif // ABSTRACTTOURNAMENTMODELSCONTEXT_H

