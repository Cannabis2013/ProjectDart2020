#ifndef ABSTRACTTOURNAMENTMODELSCONTEXT_H
#define ABSTRACTTOURNAMENTMODELSCONTEXT_H

#include "idatacontext.h"
#include "modelbuildercontext.h"
#include "idatamodelbuilder.h"
#include <qobject.h>
#include "iresponseinterface.h"

typedef QList<QPair<QUuid,QString>> PlayerPairs;

class AbstractTournamentModelsContext : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT

public slots:
    virtual void assembleAndAddTournament(const QString &title,
                                          const int &gameMode,
                                          const int &numberOfThrows,
                                          const int &winCondition,
                                          const int &keyPoint,
                                          const QList<QUuid> &assignedPlayersID) = 0;
    virtual void handleAssignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) = 0;
    virtual void deleteTournaments(const QVector<int>&indexes) = 0;
    virtual void handleTransmitPlayerScores(const QUuid &tournament,
                                            const QList<QPair<QUuid, QString> > &players) = 0;
    virtual void handleRequestAssignedPlayers(const QUuid &tournament) = 0;
    virtual void handleTransmitTournaments() = 0;
    virtual void handleRequestForTournamentMetaData(const QUuid &tournament) = 0;
    virtual void handleRequestTournamentDetails(const int &index) = 0;
    virtual void handleRequestTournamentIndexes(const QUuid &tournament) = 0;
    virtual void addScore(const QUuid &tournament,
                          const QUuid &playerID,
                          const int &roundIndex,
                          const int &setIndex,
                          const int &throwIndex,
                          const int &point,
                          const int &score,
                          const bool &isWinnerDetermined) = 0;
    virtual void handleRequestUpdateContext(const QUuid &tournamentID,
                                            const int &roundIndex,
                                            const int &setIndex) = 0;
    virtual void handleRequestSetScoreHint(const QUuid &tournament,
                                           const QUuid &player,
                                           const int &roundIndex,
                                           const int &throwIndex,
                                           const int &hint) = 0;
    virtual void handleResetTournament(const QUuid &tournament) = 0;
signals:
    void transmitResponse(const int &status, const QVariantList &arguments) override;
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
                            const QUuid &winner,
                            const QList<QUuid> &assignedPlayers);
    void sendTournamentDetails(const QUuid &tournament,
                               const QUuid &winner,
                               const int &keyPoint,
                               const int &terminalKeyCode,
                               const int &numberOfThrows,
                               const int &gameMode,
                               const QList<QUuid> &assignedPlayersID);
    void sendTournamentIndexes(const int &roundIndex,
                               const int &setIndex,
                               const int &throwIndex,
                               const int &turnIndex,
                               const int &totalTurns ,
                               const QList<int> &playerScores);
    void scoreAddedToDataContext(const QUuid &playerID,
                                     const int &point,
                                     const int &score);
    void datacontextUpdated();
    void scoreHintUpdated(const QUuid &player, const int &point, const int &score);
    void scoreHintNotUpdated(const QUuid &player, const char *err);
    void tournamentResetSuccess();
    void tournamentsDeletedSuccess(const bool &status);

    void lastTournamentTransmitted();
};

#endif // ABSTRACTTOURNAMENTMODELSCONTEXT_H
