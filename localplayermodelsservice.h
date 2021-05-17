#ifndef LOCALPLAYERCONTEXT_H
#define LOCALPLAYERCONTEXT_H

#include "iplayermodelsservice.h"
#include "abstractjsonpersistence.h"
#include "imodelsdbcontext.h"
#include "playermodel.h"

using namespace std;


class LocalPlayerModelsService :
        public IPlayerModelsService
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

    static LocalPlayerModelsService* createInstance();
    const QUuid addPlayerModelToDb(const IPlayerModel*model) override;
    bool deletePlayer(const int &index) override;
    bool deletePlayersByIndexes(const QVector<int>& indexes) override;

    LocalPlayerModelsService* setModelDBContext(IModelsDbContext *context);
    /*
     * PlayerModelsInterface interface
     */
    QVector<QString> assemblePlayerMailAdressesFromIds(const QVector<QUuid> &ids) const override;
    QVector<QString> assemblePlayerNamesFromIds(const QVector<QUuid> &ids) const override;
    QVector<QUuid> assemblePlayerIds(const QVector<int> &indexes) const override;

    void deletePlayerByUserName(const QString &firstName)  override;
    void deletePlayerByID(const QUuid &player)  override;
    void deletePlayerByEmail(const QString &playerEMail)  override;
    QUuid playerIdFromName(const QString &fullName) const override;
    QUuid playerIdFromIndex(const int &index) const override;
    QString playerNameById(const QUuid &id) const override;
    QString playerMailFromId(const QUuid &id) const override;
    QList<QUuid> players() const override;
    int playersCount() const override;
private:
    const IPlayerModel *getModel(const QString &playerName) const;
    IModelsDbContext *modelDBContext() const;
    IModelsDbContext* _dbContext;
};

#endif // LOCALPLAYERCONTEXT_H
