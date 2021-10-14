#ifndef IDARTSINDEXESDBCONTEXT_H
#define IDARTSINDEXESDBCONTEXT_H

#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "icreatedartsinexesmodels.h"
#include "idartsindexesjsonbuilder.h"
#include "ModelsContext/MCDbSLAs/IDbPersistence.h"

class IDartsIndexesDbContext : public IModelsDbContext,
        public IDbPersistence<IDartsIndexesJsonBuilder, IDartsIndexesBuilder>
{
public:
    virtual IDartsIndexesDbContext *add(IModel<QUuid> *model) = 0;
    virtual IModel<QUuid> *model(const int &index) const = 0;
    virtual QVector<IModel<QUuid>*> models() const = 0;
    virtual IDartsIndexesDbContext *remove(const int &index) = 0;
    virtual int indexOf(IModel<QUuid> *model) const = 0;
    virtual IDartsIndexesDbContext *replace(const int &index, IModel<QUuid> *model) = 0;
    virtual void fetchModels(const IDartsIndexesBuilder* modelBuilder) = 0;
    virtual void saveChanges(const IDartsIndexesJsonBuilder *jsonBuilder) = 0;
};
#endif // IDARTSINDEXESDBCONTEXT_H
