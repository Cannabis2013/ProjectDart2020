#ifndef IDUPLICATECHECKER_H
#define IDUPLICATECHECKER_H
#include "PlayerModelsContext/DbSLAs/IPlayersDbContext.h"
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
class IDuplicateChecker
{
public:
    typedef IModel<QUuid> BaseModel;
    virtual bool isDup(BaseModel* player, IPlayersDbContext *dbContext) const = 0;
};
#endif // IDUPLICATECHECKER_H
