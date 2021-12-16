#ifndef DUPLICATECHECKER_H
#define DUPLICATECHECKER_H
#include "PlayerModelsContext/ModelsSLAs/iduplicatechecker.h"
#include "PlayerModelsContext/DbSLAs/IPlayersDbContext.h"
#include "PlayerModelsContext/DbSLAs/iplayer.h"
class DuplicateChecker : public IDuplicateChecker<IPlayer,IPlayersDbContext<IPlayer>>
{
public:
    virtual bool isDup(BaseModel* model, DbContext *dbContext) const override
    {
        auto player = dynamic_cast<IPlayer*>(model);
        auto models = dbContext->models();
        auto result = checkForDuplicate(player->name(),models);
        return result;
    }
private:
    bool checkForDuplicate(const QString &name, const QVector<BaseModel*> &models) const
    {
        for (const auto &model : models) {
            auto player = dynamic_cast<IPlayer*>(model);
            if(player->name() == name)
                return true;
        }
        return false;
    }
};
#endif // DUPLICATECHECKER_H
