#ifndef DUPLICATECHECKER_H
#define DUPLICATECHECKER_H

#include <PlayerModelsContext/ModelsSLAs/iduplicatechecker.h>

template<typename T>
class QVector;
class QString;
template<typename T>
class IPlayersDbContext;
class IPlayer;

class DuplicateChecker : public IDuplicateChecker<IPlayer,IPlayersDbContext<IPlayer>>
{
public:
    virtual bool isDup(BaseModel* model, DbContext *dbContext) const override;
private:
    bool checkForDuplicate(const QString &name, const QVector<BaseModel*> &models) const;
};
#endif // DUPLICATECHECKER_H
