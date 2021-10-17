#ifndef RESETDARTSINDEXES_H
#define RESETDARTSINDEXES_H

#include "DartsModelsContext/IndexesSLAs/iresetdartsindexes.h"

class ResetDartsIndexes: public IResetDartsIndexes
{
public:
    IDartsIndexesDbContext *reset(const QUuid &tournamentId, const IDartsIndexesBuilder *builderContext,
                                  IDartsIndexesDbContext *dbContext) const
    {
        auto models = dbContext->models();
        auto indexes = getModelByTournamentId(tournamentId,models);
        auto indexOf = dbContext->indexOf(indexes);
        auto initialIndexes = builderContext->buildIndexes(tournamentId);
        dbContext->replace(indexOf,initialIndexes);
        return dbContext;
    };
private:
    IDartsIndexes *getModelByTournamentId(const QUuid &tournamentId, const QVector<IModel<QUuid>*> &models) const
    {
        for (auto &model : models) {
            auto indexes = dynamic_cast<IDartsIndexes*>(model);
            if(indexes->tournamentId() == tournamentId)
                return indexes;
        }
        return nullptr;
    }
};
#endif // RESETDARTSINDEXES_H
