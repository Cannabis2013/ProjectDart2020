#ifndef IDARTSINPUTSDBCONTEXT_H
#define IDARTSINPUTSDBCONTEXT_H
#include "ModelsContext/DbSLAs/IDbPersistence.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "idartsinputbuilder.h"
#include "idartsinputjsonbuilder.h"

class IDartsInputsDbContext : public IModelsDbContext,
        public IDbPersistence<IDartsInputJsonBuilder,IDartsInputBuilder>
{
public:
    virtual IDartsInputsDbContext *add(IModel<QUuid> *inputModel) = 0;
    virtual IModel<QUuid> *model(const int &) const = 0;
    virtual QVector<IModel<QUuid>*> models() const = 0;
    virtual IDartsInputsDbContext *remove(const int &) = 0;
    virtual int indexOf(IModel<QUuid> *model) const = 0;
    virtual IDartsInputsDbContext *replace(const int &index, IModel<QUuid> *model) = 0;
    virtual void fetchModels(const IDartsInputBuilder *modelBuilder) = 0;
    virtual void saveChanges(const IDartsInputJsonBuilder *jsonBuilder) = 0;
};

#endif // IDARTSINPUTSDBCONTEXT_H
