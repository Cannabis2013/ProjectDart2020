#ifndef ABSTRACTPLAYERMODELSCONTEXT_H
#define ABSTRACTPLAYERMODELSCONTEXT_H

#include <quuid.h>
#include "persistenceinterface.h"

class IPlayerModelsContext
{
public:
    virtual ~IPlayerModelsContext()=default;
    virtual QUuid createPlayer(const QString &name,
                              const QString& mail,
                              const int &role = -1) = 0;
    virtual bool deletePlayer(const int &index) = 0;
    virtual bool deletePlayers(const QVector<int>& indexes) = 0;
    virtual QVector<QString> assemblePlayerMailAdressesFromIds(const QVector<QUuid> &ids) = 0;
    virtual QVector<QString> assemblePlayerNamesFromIds(const QVector<QUuid> &ids) = 0;
    virtual QVector<QUuid> assemblePlayerIds(const QVector<int> &indexes) = 0;
    virtual void deletePlayerByUserName(const QString &firstName)  = 0;
    virtual void deletePlayerByID(const QUuid &player)  = 0;
    virtual void deletePlayerByEmail(const QString &playerEMail)  = 0;
    virtual QUuid playerIdFromName(const QString &fullName)  = 0;
    virtual QUuid playerIdFromIndex(const int &index)  = 0;
    virtual QString playerNameFromId(const QUuid &id)  = 0;
    virtual QString playerMailFromId(const QUuid &id)  = 0;
    virtual QList<QUuid> players() = 0;
    virtual int playersCount() = 0;
};

#endif // ABSTRACTPLAYERMODELSCONTEXT_H
