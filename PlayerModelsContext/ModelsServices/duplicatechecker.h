#ifndef DUPLICATECHECKER_H
#define DUPLICATECHECKER_H
#include "PlayerModelsContext/ModelsSLAs/iduplicatechecker.h"
class DuplicateChecker : public IDuplicateChecker
{
public:
    virtual bool isDup(BaseModel* model, IPlayersDbContext *dbContext) const override
    {
        auto player = dynamic_cast<IPlayerModel*>(model);
        auto models = dbContext->models();
        auto result = checkForDuplicate(player->name(),models);
        return result;
    }
private:
    bool checkForDuplicate(const QString &name, const QVector<IModel<QUuid>*> &models) const
    {
        for (const auto &model : models) {
            auto player = dynamic_cast<IPlayerModel*>(model);
            if(player->name() == name)
                return true;
        }
        return false;
    }
};
#endif // DUPLICATECHECKER_H
