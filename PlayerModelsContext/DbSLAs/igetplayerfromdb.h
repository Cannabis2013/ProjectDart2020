#ifndef IGETPLAYERSFROMDB_H
#define IGETPLAYERSFROMDB_H
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include <qvector.h>
class IGetPlayersFromDb
{
public:
    typedef IModel<QUuid> Player;
    typedef QVector<Player*> Players;
    virtual Player *player(const QUuid &id, const IModelsDbContext *dbContext) const = 0;
    virtual Player *player(const QString &name, const IModelsDbContext *dbContext) const = 0;
    virtual Players players(const QVector<int> &indexes, const IModelsDbContext *dbContext) const = 0;
    virtual Players players(const QVector<QUuid> &ids, const IModelsDbContext *dbContext) const = 0;
    virtual Players players(const QVector<QString> &names, const IModelsDbContext *dbContext) const = 0;
};
#endif // IGETDARTSPLAYERDATAFROMDB_H
