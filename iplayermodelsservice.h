#ifndef ABSTRACTPLAYERMODELSCONTEXT_H
#define ABSTRACTPLAYERMODELSCONTEXT_H

#include <quuid.h>
#include "ipersistence.h"
#include <iplayermodel.h>

class IPlayerModelsService
{
public:
    virtual ~IPlayerModelsService()=default;
    virtual const QUuid addPlayerModelToDb(const IPlayerModel*) = 0;
    virtual bool deletePlayer(const int &index) = 0;
    virtual bool deletePlayersByIndexes(const QVector<int>& indexes) = 0;
    virtual QVector<QString> assemblePlayerMailAdressesFromIds(const QVector<QUuid> &ids) const = 0;
    virtual QVector<QString> assemblePlayerNamesFromIds(const QVector<QUuid> &ids) const = 0;
    virtual QVector<QUuid> assemblePlayerIds(const QVector<int> &indexes) const = 0;
    virtual void deletePlayerByUserName(const QString &firstName)  = 0;
    virtual void deletePlayerByID(const QUuid &player)  = 0;
    virtual void deletePlayerByEmail(const QString &playerEMail) = 0;
    virtual QUuid playerIdFromName(const QString &fullName) const = 0;
    virtual QUuid playerIdFromIndex(const int &index) const = 0;
    virtual QString playerNameById(const QUuid &id) const  = 0;
    virtual QString playerMailFromId(const QUuid &id) const  = 0;
    virtual QList<QUuid> players() const = 0;
    virtual int playersCount() const = 0;
};

#endif // ABSTRACTPLAYERMODELSCONTEXT_H
