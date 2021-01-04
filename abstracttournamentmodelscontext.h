#ifndef ABSTRACTTOURNAMENTMODELSCONTEXT_H
#define ABSTRACTTOURNAMENTMODELSCONTEXT_H

#include <qobject.h>
#include "itournamentmodelbuilder.h"
#include "iresponseinterface.h"
#include "modelbuildercontext.h"
#include "iscoremodel.h"
#include "imodelsdbcontext.h"

#define CREATE_TOURNAMENT_PARAMS_SIZE 5

typedef QList<QPair<QUuid,QString>> PlayerPairs;

typedef ITournament<QUuid,QList<QUuid>,QString> DefaultTournamentInterface;
typedef IScore<QUuid> DefaultScoreInterface;

typedef ITournamentModelBuilder<DefaultTournamentInterface,
                                TournamentParameters,
                                DefaultScoreInterface,
                                ScoreParameters,
                                ModelOptions> DefaultTournamentModelBuilder;

class IModelParameter
{
public:
    virtual bool generateID() = 0;
    virtual IModelParameter *setGenerateID(const bool &) = 0;
};

class AbstractTournamentModelsContext : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public:
    virtual ~AbstractTournamentModelsContext() =default;
    /*
     * Setup/read initial values
     */
    virtual AbstractTournamentModelsContext *setup() = 0;
    /*
     * Builders
     */
    virtual AbstractTournamentModelsContext *setModelBuilder(DefaultTournamentModelBuilder *builder) = 0;
    virtual DefaultTournamentModelBuilder *modelBuilder() = 0;
    virtual AbstractTournamentModelsContext *setModelDBContext(ImodelsDBContext<IModel<QUuid>, QString> *context) = 0;
public slots:
    virtual void assembleAndAddTournament(const QString &title,
                                          const QList<int> &data,
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
                          const QList<int> &dataValues,
                          const bool &isWinnerDetermined) = 0;
    virtual void handleRequestSetScoreHint(const QUuid &tournament,
                                           const QUuid &player,
                                           const int &roundIndex,
                                           const int &throwIndex,
                                           const int &hint) = 0;
    virtual void handleResetTournament(const QUuid &tournament) = 0;
signals:
    void transmitResponse(const int &status, const QVariantList &arguments) override;
    void sendPlayerScore(const QString &player, const int &point, const int &score, const int &keyCode);
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
                            const int &tableViewHint,
                            const QUuid &winner,
                            const QList<QUuid> &assignedPlayers);
    void sendTournamentDetails(const QUuid &tournament,
                               const QUuid &winner,
                               const int &keyPoint,
                               const int &inputMode,
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

