#ifndef UPDATEDARTSINDEXES_H
#define UPDATEDARTSINDEXES_H
#include "IndexesSLAs/iupdatedartsindexes.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include <qvector.h>
class UpdateDartsIndexes : public IUpdateDartsIndexes<IModel<QUuid>>
{
public:
    IDbContext<BaseModel> *update(IDartsIndex *index, const QUuid &tournament, IDbContext<BaseModel> *dbContext) const override
    {
        for (auto &model : dbContext->models()) {
            if(matchByTournamentId(model,tournament))
                updateTournament(index,model);
        }
        return dbContext;
    }
private:
    bool matchByTournamentId(IModel<QUuid> *model, const QUuid &tournamentId) const
    {
        auto tournament = dynamic_cast<IDartsTournament*>(model);
        return tournament->id() == tournamentId;
    }
    void updateTournament(IDartsIndex *index, IModel<QUuid> *model) const
    {
        auto dartsTournament = dynamic_cast<IDartsTournament*>(model);
        dartsTournament->setTotalTurns(index->totalTurns());
        dartsTournament->setTurnIndex(index->turnIndex());
        dartsTournament->setRoundIndex(index->roundIndex());
        dartsTournament->setSetIndex(index->playerIndex());
        dartsTournament->setAttemptIndex(index->attemptIndex());
    }
};

#endif // UPDATEDARTSINDEXES_H
