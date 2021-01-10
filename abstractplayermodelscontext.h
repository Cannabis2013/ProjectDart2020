#ifndef ABSTRACTPLAYERMODELSCONTEXT_H
#define ABSTRACTPLAYERMODELSCONTEXT_H

#include <qobject.h>
#include <quuid.h>
#include "iplayermodel.h"
#include "iplayermodelbuilder.h"
#include "iplayerbuildercontext.h"
#include "iresponseinterface.h"
#include "imodelsdbcontext.h"

#define CREATE_TOURNAMENT_PARAMS_SIZE 5

typedef IPlayerModel<QUuid,QString> DefaultPlayerModelInterface;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParametersInterface;
typedef IPlayerModelOptions<QUuid> DefaultOptionsInterface;
typedef IPlayerModelBuilder<DefaultPlayerModelInterface,DefaultParametersInterface,DefaultOptionsInterface> DefaultPlayerBuilder;
typedef QList<QPair<QUuid,QString>> PlayerPairs;

class AbstractPlayerModelsContext : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public:
    virtual ~AbstractPlayerModelsContext()=default;

    virtual AbstractPlayerModelsContext* setup() = 0;
    virtual AbstractPlayerModelsContext* setPlayerBuilder(DefaultPlayerBuilder *builder) = 0;
    virtual AbstractPlayerModelsContext *setModelDBContext(ImodelsDBContext<DefaultPlayerModelInterface,QUuid> *context) = 0;
public slots:
    virtual void createPlayer(const QString &name, const QString &mail) = 0;
    virtual void deletePlayer(const int &index) = 0;
    virtual void deletePlayers(const QVector<int> &playerIndexes) = 0;
    virtual void assembleListOfPlayersFromIndexes(const QVector<int> &playerIndexes) = 0;
    virtual void processTournamentDetails(const QUuid &tournament,
                                          const QUuid &winner,
                                          const QList<int> &parameters,
                                          const QList<QUuid> &assignedPlayersID,
                                          const QList<int> &scores) = 0;

    virtual void handleAndProcessTournamentMetaData(const QString &title,
                                                    const int &gameMode,
                                                    const int &keyPoint,
                                                    const int &tableViewHint,
                                                    const int &inputMode,
                                                    const QUuid &winnerID,
                                                    const QList<QUuid> &assignedPlayersID) = 0;
    virtual void handleRequestPlayersDetails() = 0;
    virtual void handleAndProcessCreatedTournament(const QString &title,
                                                   const QList<int> &data,
                                                   const QList<int> &playerIndexes) = 0;


signals:
    void transmitResponse(const int &status, const QVariantList &arguments) override;
    void sendPlayerDetails(const QString &playerName, const QString &mail);
    void sendPlayersID(const QList<QUuid> &playersID);
    void sendTournamentDetails(const QUuid &tournament,
                               const QUuid &winner,
                               const QList<int> &parameters,
                               const QList<QUuid> &playerIds,
                               const QList<QString>& playerNames,
                               const QList<int>& scores);
    void sendProcessedTournamentMetaData(const QString &title,
                                         const int &gameMode,
                                         const int &keyPoint,
                                         const int &tableViewHint,
                                         const int &inputMode,
                                         const QString &winner,
                                         const QStringList &assignedPlayerNames);
    void sendCurrentAssignedPlayerPairs(const QUuid &tournament,
                                        const PlayerPairs &playerPairs);
    void sendProcessedTournamentDetails(const QString &title,
                                        const QList<int> &data,
                                        const QList<QUuid> &playersID);
    void playersDeletedStatus(const bool &status);
    void lastPlayerDetailTransmitted();

    void confirmPlayerCreated(const bool &status);
};

#endif // ABSTRACTPLAYERMODELSCONTEXT_H
