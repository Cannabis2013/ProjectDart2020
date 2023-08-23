#ifndef DUPLICATECHECKER_H
#define DUPLICATECHECKER_H

#include <PlayerModelsContext/Contracts/ModelsSLAs/iduplicatechecker.h>

#include <PlayerModelsContext/Contracts/DbSLAs/IPlayersDbContext.h>
#include <PlayerModelsContext/Contracts/DbSLAs/iplayer.h>

class DuplicateChecker : public IDuplicateChecker<IPlayer,IPlayersDbContext<IPlayer>>
{
public:
    virtual bool isDup(BaseModel* model, DbContext *dbContext) const override;
private:
    bool checkForDuplicate(const QString &name, const QVector<BaseModel*> &models) const;
};
#endif // DUPLICATECHECKER_H
