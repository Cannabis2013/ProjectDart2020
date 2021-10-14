#ifndef IDARTSDBCONTEXT_H
#define IDARTSDBCONTEXT_H
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "ModelsContext/MCDbSLAs/IDbPersistence.h"
#include "DartsModelsContext/TournamentsDbSLAs/idartstournamentbuilder.h"
#include "itournamentjsonbuilder.h"
class IDartsDbContext : public IModelsDbContext,
        public IDbPersistence<ITournamentJsonBuilder,IDartsTournamentBuilder>
{
public:
    virtual IDartsDbContext *add(IModel<QUuid> *model) = 0;
    virtual QVector<IModel<QUuid>*> models() const = 0;
    virtual IDartsDbContext *remove(const int &) = 0;
    virtual IDartsDbContext *remove(const QVector<int> &indexes) = 0;
    virtual int indexOf(IModel<QUuid> *model) const = 0;
    virtual IDartsDbContext *replace(const int &index, IModel<QUuid> *model) = 0;
    virtual void fetchModels(const IDartsTournamentBuilder *modelBuilder) = 0;
    virtual void saveChanges(const ITournamentJsonBuilder *jsonBuilder) = 0;
};
#endif // IDARTSDBCONTEXT_H
