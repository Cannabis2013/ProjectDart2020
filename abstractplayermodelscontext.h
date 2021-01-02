#ifndef ABSTRACTPLAYERMODELSCONTEXT_H
#define ABSTRACTPLAYERMODELSCONTEXT_H

#include <qobject.h>
#include <quuid.h>
#include "iplayermodel.h"
#include "iplayermodelbuilder.h"
#include "iplayerbuildercontext.h"
#include "iresponseinterface.h"
#include "imodelsdbcontext.h"

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
                                             const int &keyPoint,
                                             const int &terminalKeyCode,
                                             const int &numberOfThrows,
                                             const int &gameMode,
                                             const QList<QUuid> &players) = 0;

    virtual void handleAndProcessTournamentMetaData(const QString &title,
                                                    const int &gameMode,
                                                    const int &keyPoint,
                                                    const int &tableViewHint,
                                                    const QUuid &winnerID,
                                                    const QList<QUuid> &assignedPlayersID) = 0;
    virtual void handleRequestPlayersDetails() = 0;
    virtual void handleAndProcessCreatedTournament(const QString &title,
                                                   const int &numberOfThrows,
                                                   const int &gameMode,
                                                   const int &winCondition,
                                                   const int &displayHint,
                                                   const int &keyPoint,
                                                   const QList<int> &playerIndexes) = 0;


signals:
    void transmitResponse(const int &status, const QVariantList &arguments) override;
    void sendPlayerDetails(const QString &playerName, const QString &mail);
    void sendPlayersID(const QList<QUuid> &playersID);
    void sendTournamentDetails(const QUuid &tournament,
                               const QString &winner,
                               const int &keyPoint,
                               const int &terminalKeyCode,
                               const int &numberOfThrows,
                               const int &gameMode,
                               const PlayerPairs &assignedPlayerPairs);
    void sendProcessedTournamentMetaData(const QString &title,
                                         const int &gameMode,
                                         const int &keyPoint,
                                         const int &tableViewHint,
                                         const QString &winner,
                                         const QStringList &assignedPlayerNames);
    void sendCurrentAssignedPlayerPairs(const QUuid &tournament,
                                        const PlayerPairs &playerPairs);
    void sendProcessedTournamentDetails(const QString &title,
                                        const int &gameMode,
                                        const int &numberOfThrows,
                                        const int &winCondition,
                                        const int &displayHint,
                                        const int &keyPoint,
                                        const QList<QUuid> &playersID);
    void playersDeletedStatus(const bool &status);
    void lastPlayerDetailTransmitted();

    void confirmPlayerCreated(const bool &status);
};

#endif // ABSTRACTPLAYERMODELSCONTEXT_H
