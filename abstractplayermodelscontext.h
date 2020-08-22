#ifndef ABSTRACTPLAYERMODELSCONTEXT_H
#define ABSTRACTPLAYERMODELSCONTEXT_H

#include "iplayermodel.h"
#include "iplayercontext.h"
#include <quuid.h>
#include "iplayerbuildercontext.h"
#include "idatamodelbuilder.h"
#include <qobject.h>

typedef IPlayerModel<QUuid,QString> DefaultPlayerInterface;
typedef IDataModelBuilder<DefaultPlayerInterface,IPlayerBuilderParameters<QString,QUuid>,IPlayerBuilderConfiguration> DefaultPlayerBuilder;
typedef IPlayerContext<QUuid,QList<QUuid>,QString,DefaultPlayerBuilder> PlayerContextInterface;

typedef QList<QPair<QUuid,QString>> PlayerPairs;

class AbstractPlayerModelsContext : public QObject
{
    Q_OBJECT
public:
    AbstractPlayerModelsContext();

public slots:
    virtual void handleCreatePlayerRequest(const QString &name, const QString &mail) = 0;
    virtual void handleDeletePlayerRequest(const int &index) = 0;
    virtual void handleDeletePlayersRequest(const QVector<int> &playerIndexes) = 0;
    virtual void handlePlayersFromIndexRequest(const QVector<int> &playerIndexes) = 0;
    virtual void assembleAssignedPlayerPairs(const QUuid &tournament,
                                                  const QList<QUuid> &players) = 0;

    virtual void handleProcessTournamentMeta(const QString &title,
                                              const int &gameMode,
                                              const int &keyPoint,
                                              const QList<QUuid> &assignedPlayersID) = 0;
    virtual void handleRequestPlayersDetails() = 0;


signals:
    void sendPlayerDetails(const QString &playerName, const QString &mail);
    void sendPlayersID(const QList<QUuid> &playersID);
    void confirmPlayerCreated(const bool &status);
    void confirmPlayersDeleted(const bool &status);

    void sendPlayerPairs(const QUuid &tournament,const PlayerPairs &pairs);

    void sendProcessedTournamentMeta(const QString &title,
                                     const int &gameMode,
                                     const int &keyPoint,
                                     const QStringList &assignedPlayerNames);
    void sendCurrentAssignedPlayerPairs(const QUuid &tournament,
                                        const PlayerPairs &playerPairs);

    // Test purposes
    friend class ApplicationInterface;
};

#endif // ABSTRACTPLAYERMODELSCONTEXT_H
