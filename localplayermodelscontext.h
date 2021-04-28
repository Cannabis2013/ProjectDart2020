#ifndef LOCALPLAYERCONTEXT_H
#define LOCALPLAYERCONTEXT_H

#include <quuid.h>
#include <QString>
#include <qlist.h>
#include <qobject.h>
#include <iostream>
#include <QVariantList>
#include "iplayermodel.h"
#include "iplayermodelscontext.h"
#include "playermodelbuildercontext.h"
#include "abstractjsonpersistence.h"
#include "iplayermodelbuilder.h"
#include "imodelsdbcontext.h"


using namespace std;

typedef IPlayerModel<QUuid,QString> IDefaultPlayerModel;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParametersInterface;
typedef IPlayerModelOptions<QUuid> DefaultOptionsInterface;
typedef IPlayerModelBuilder<IDefaultPlayerModel,DefaultParametersInterface,DefaultOptionsInterface> DefaultPlayerBuilder;
typedef QList<QPair<QUuid,QString>> PlayerPairs;

namespace PlayerContext {
    class LocalPlayerContext;
    class PlayerModelOptions;
    class PlayerBuilderParameters;
}

typedef IPlayerModel<QUuid,QString> IDefaultPlayerModel;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParametersInterface;

class LocalPlayerModelsContext :
        public IPlayerModelsContext
{
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

    LocalPlayerModelsContext* setup();

    static LocalPlayerModelsContext* createInstance()
    {
        return new LocalPlayerModelsContext();
    }

    ~LocalPlayerModelsContext();

    QUuid createPlayer(const QString &name,
                      const QString& mail,
                      const int &role = -1) override;
    bool deletePlayer(const int &index) override;
    bool deletePlayers(const QVector<int>& indexes) override;

    DefaultPlayerBuilder *playerBuilder();
    LocalPlayerModelsContext* setPlayerBuilder(DefaultPlayerBuilder *builder);
    LocalPlayerModelsContext* setModelDBContext(IModelsDbContext *context);
    /*
     * PlayerModelsInterface interface
     */
    QVector<QString> assemblePlayerMailAdressesFromIds(const QVector<QUuid> &ids) override;
    QVector<QString> assemblePlayerNamesFromIds(const QVector<QUuid> &ids) override;
    QVector<QUuid> assemblePlayerIds(const QVector<int> &indexes) override;

    void deletePlayerByUserName(const QString &firstName)  override;
    void deletePlayerByID(const QUuid &player)  override;
    void deletePlayerByEmail(const QString &playerEMail)  override;
    QUuid playerIdFromName(const QString &fullName)  override;
    QUuid playerIdFromIndex(const int &index)  override;
    QString playerNameFromId(const QUuid &id)  override;
    QString playerMailFromId(const QUuid &id)  override;
    QList<QUuid> players() override;
    int playersCount() override;
private:

    DefaultPlayerBuilder *playerBuilder() const;


    QUuid buildPlayerModel(const QString &playerName,
                           const QString& email,
                           const int &role,
                           const bool &generateID = true,
                           const QUuid &id = QUuid());

    const IDefaultPlayerModel *getModel(const QString &playerName);

    IModelsDbContext *modelDBContext();

    IModelsDbContext* _dbContext;
    DefaultPlayerBuilder *_playerBuilder;
};

#endif // LOCALPLAYERCONTEXT_H
