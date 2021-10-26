#ifndef IDARTSDBCONTEXT_H
#define IDARTSDBCONTEXT_H
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "ModelsContext/DbSLAs/IDbPersistence.h"
#include "DartsModelsContext/TournamentsDbSLAs/idartsbuilder.h"
#include "itournamentjsonbuilder.h"
class IDartsDbContext : public IModelsDbContext,
        public IDbPersistence<IDartsJsonBuilder,IDartsBuilder>
{
public:
    virtual IDartsDbContext *add(IModel<QUuid> *model) = 0;
    virtual QVector<IModel<QUuid>*> models() const = 0;
    virtual IDartsDbContext *remove(const int &) = 0;
    virtual IDartsDbContext *remove(const QVector<int> &indexes) = 0;
    virtual int indexOf(IModel<QUuid> *model) const = 0;
    virtual IDartsDbContext *replace(const int &index, IModel<QUuid> *model) = 0;
    virtual void fetchModels(const IDartsBuilder *modelBuilder) = 0;
    virtual void saveChanges(const IDartsJsonBuilder *jsonBuilder) = 0;
};
#endif // IDARTSDBCONTEXT_H
