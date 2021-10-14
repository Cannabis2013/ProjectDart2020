#ifndef IPLAYERSDBCONTEXT_H
#define IPLAYERSDBCONTEXT_H

#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "ModelsContext/MCDbSLAs/IDbPersistence.h"
#include "PlayerModelsContext/DbSLAs/iplayercontextmodelbuilder.h"
#include "PlayerModelsContext/DbSLAs/iplayercontextjsonbuilder.h"

class IPlayersDbContext : public IModelsDbContext, public IDbPersistence<IPlayerContextJsonBuilder,IPlayerContextModelBuilder>
{
public:
    virtual IPlayersDbContext *add(IModel<QUuid> *model) = 0;
    virtual IModel<QUuid> *model(const int &) const = 0;
    virtual QVector<IModel<QUuid> *> models() const = 0;
    virtual IPlayersDbContext *remove(const int &index) = 0;
    virtual IPlayersDbContext *remove(const QVector<int> &indexes) = 0;
    virtual int indexOf(IModel<QUuid> *model) const = 0;
    virtual IPlayersDbContext *replace(const int &index, IModel<QUuid> *model) = 0;
    virtual void fetchModels(const IPlayerContextModelBuilder *modelBuilder) = 0;
    virtual void saveChanges(const IPlayerContextJsonBuilder *jsonBuilder) = 0;
};
#endif // IPLAYERSDBCONTEXT_H
