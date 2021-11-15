#ifndef IDARTSINPUTSDBCONTEXT_H
#define IDARTSINPUTSDBCONTEXT_H
#include "ModelsContext/DbSLAs/IDbPersistence.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "idartsinputbuilder.h"
#include "idartsinputjsonbuilder.h"
#include <qfuture.h>

class IDartsInputsDbContext : public IModelsDbContext,
        public IDbPersistence<IDartsInputJsonBuilder,IDartsInputBuilder,QFuture<bool>>
{
public:
    virtual IDartsInputsDbContext *add(IModel<QUuid> *inputModel) = 0;
    virtual IModel<QUuid> *model(const int &) const = 0;
    virtual QVector<IModel<QUuid>*> models() const = 0;
    virtual IDartsInputsDbContext *remove(const int &) = 0;
    virtual int indexOf(IModel<QUuid> *model) const = 0;
    virtual IDartsInputsDbContext *replace(const int &index, IModel<QUuid> *model) = 0;
    virtual bool fetch(const IDartsInputBuilder *modelBuilder) = 0;
    virtual QFuture<bool> saveChanges(const IDartsInputJsonBuilder *jsonBuilder) = 0;
};

#endif // IDARTSINPUTSDBCONTEXT_H
