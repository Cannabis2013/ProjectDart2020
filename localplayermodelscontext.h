#ifndef LOCALPLAYERCONTEXT_H
#define LOCALPLAYERCONTEXT_H

#include "iplayermodel.h"
#include <quuid.h>
#include <QString>
#include <qlist.h>
#include <qobject.h>
#include "abstractplayermodelscontext.h"
#include "defaultplayerbuilderconfigurations.h"
#include <QVariantList>
#include <iostream>
#include "abstractjsonpersistence.h"

using namespace std;

namespace PlayerContext {
    class LocalPlayerContext;
    class PlayerModelOptions;
    class PlayerBuilderParameters;
}

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParameters;
typedef IDataModelBuilder<DefaultModelInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;

class LocalPlayerModelsContext :
        public AbstractPlayerModelsContext,
        public AbstractJSONPersistence
{
    Q_OBJECT
public:
    /*
     * Public types
     */
    enum ContextResponse{
        PlayerCreatedOK = 0x33,
        PlayerDeletedOK = 0x34,
        PlayersDeletedOK = 0x36,
        InconsistencyDetected = 0x39
    };
    enum UserRoles{Admin = 0x0, Player = 0x02};

    AbstractPlayerModelsContext *setup() override;

    static AbstractPlayerModelsContext* createInstance()
    {
        return new LocalPlayerModelsContext();
    }



    ~LocalPlayerModelsContext();
    // PersistenceInterface interface
    void read() override;
    void write() override;

    DefaultPlayerBuilder *playerBuilder();
    AbstractPlayerModelsContext* setPlayerBuilder(DefaultPlayerBuilder *builder) override;
    AbstractPlayerModelsContext* setModelDBContext(IModelDBContext<IDefaultPlayerModel, QUuid> *context) override;
public slots:
    void createPlayer(const QString &name, const QString &mail) override;
    void deletePlayer(const int &index) override;
    void deletePlayers(const QVector<int> &playerIndexes) override;
    void assembleListOfPlayersFromIndexes(const QVector<int> &playerIndexes) override;
    void processTournamentDetails(const QUuid &tournament,
                                     const QUuid &winner,
                                     const int &keyPoint,
                                     const int &terminalKeyCode,
                                     const int &numberOfThrows,
                                     const int &gameMode,
                                     const QList<QUuid> &players) override;
    void handleAndProcessTournamentMetaData(const QString &title,
                                            const int &gameMode,
                                            const int &keyPoint,
                                            const QUuid &winnerID,
                                            const QList<QUuid> &assignedPlayersID) override;
    void handleRequestPlayersDetails() override;
    void handleProcessCreatedTournament(const QString &title,
                                        const int &numberOfThrows,
                                        const int &gameMode,
                                        const int &winCondition,
                                        const int &keyPoint,
                                        const QList<int> &playerIndexes) override;
private:
    IModelDBContext<IDefaultPlayerModel, QUuid> *modelDBContext();

    void deletePlayerByUserName(const QString &firstName) ;
    void deletePlayerByID(const QUuid &player) ;
    void deletePlayerByEmail(const QString &playerEMail) ;
    QUuid playerIDFromName(const QString &fullName) ;
    QUuid playerIDFromIndex(const int &index) ;
    QString playerName(const QUuid &id) ;
    QString playerEMail(const QUuid &id) ;
    QList<QUuid> players() ;
    int playersCount() ;
    DefaultPlayerBuilder *playerBuilder() const;

    QJsonArray assemblePlayersJSONArray();
    void extractPlayerModelsFromJSON(const QJsonArray &arr);

    QUuid buildPlayerModel(const QString &playerName,
                          const QString& email, const int &role,
                          const bool &generateID = true,
                          const QUuid &id = QUuid()) ;

    const IDefaultPlayerModel *getModel(const QString &playerName);

    IModelDBContext<IDefaultPlayerModel,QUuid> *_dbContext;
    DefaultPlayerBuilder *_playerBuilder;
};

#endif // LOCALPLAYERCONTEXT_H
