#ifndef UPDATEDARTSINDEXES_H
#define UPDATEDARTSINDEXES_H

#include "DartsModelsContext/IndexesSLAs/iupdatedartsindexes.h"

class UpdateDartsIndexes : public IUpdateDartsIndexes
{
public:
    IDartsIndexesDbContext *update(IModel<QUuid> *model, IDartsIndexesDbContext *dbContext) const override
    {
        auto indexesRef = dynamic_cast<IDartsIndex*>(model);
        auto models = dbContext->models();
        for (int i = 0; i < models.count(); ++i) {
            if(matchByTournamentId(models.at(i),indexesRef->tournamentId()))
            {
                dbContext->replace(i,indexesRef);
                return dbContext;
            }
        }
        return dbContext;
    }
private:
    bool matchByTournamentId(IModel<QUuid> *model, const QUuid &tournamentId) const
    {
        return dynamic_cast<IDartsIndex*>(model)->tournamentId() == tournamentId;
    }
};

#endif // UPDATEDARTSINDEXES_H
