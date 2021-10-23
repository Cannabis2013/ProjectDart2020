#ifndef REMOVEDARTSINDEXES_H
#define REMOVEDARTSINDEXES_H

#include "DartsModelsContext/IndexesDbSLAs/iremovedartsindexes.h"
#include "dartsindex.h"

class RemoveDartsIndexes : public IRemoveDartsIndexes
{
public:
    virtual IDartsIndexesDbContext *removeByTournamentIds(const QVector<QUuid> &tournamentIds, IDartsIndexesDbContext *dbContext) const override
    {
        for (const auto &tournamentId : tournamentIds)
            remove(tournamentId,dbContext);
        return dbContext;
    }
private:
    void remove(const QUuid &tournamentId, IDartsIndexesDbContext *dbContext) const
    {
        auto models = dbContext->models();
        for (int i = 0; i < models.count(); ++i) {
            if(matchByTournamentId(models.at(i),tournamentId))
            {
                dbContext->remove(i);
                return;
            }
        }
    }
    bool matchByTournamentId(const IModel<QUuid> *model, const QUuid &tournamentId) const
    {
        return dynamic_cast<const DartsIndex*>(model)->tournamentId() == tournamentId;
    }
};
#endif // REMOVEDARTSINDEXES_H
