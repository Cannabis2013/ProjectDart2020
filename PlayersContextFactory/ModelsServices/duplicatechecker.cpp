#include "duplicatechecker.h"
#include "DbSLAs/IPlayersDbContext.h"
#include "DbSLAs/iplayer.h"
#include <qvector.h>
bool DuplicateChecker::isDup(BaseModel *model, DbContext *dbContext) const
{
    auto player = dynamic_cast<IPlayer*>(model);
    auto models = dbContext->models();
    auto result = checkForDuplicate(player->name(),models);
    return result;
}

bool DuplicateChecker::checkForDuplicate(const QString &name, const QVector<BaseModel *> &models) const
{
    for (const auto &model : models) {
        auto player = dynamic_cast<IPlayer*>(model);
        if(player->name() == name)
            return true;
    }
    return false;
}
