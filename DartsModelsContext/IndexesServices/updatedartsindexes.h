#ifndef UPDATEDARTSINDEXES_H
#define UPDATEDARTSINDEXES_H

#include "DartsModelsContext/IndexesSLAs/iupdatedartsindexes.h"
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"

class UpdateDartsIndexes : public IUpdateDartsIndexes
{
public:
    IDartsDbContext *update(IDartsIndex *index, const QUuid &tournament, IDartsDbContext *dbContext) const override
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
        auto tournament = dynamic_cast<AbstractDartsTournament*>(model);
        return tournament->id() == tournamentId;
    }
    void updateTournament(IDartsIndex *index, IModel<QUuid> *model) const
    {
        auto dartsTournament = dynamic_cast<AbstractDartsTournament*>(model);
        dartsTournament->setTotalTurns(index->totalTurns());
        dartsTournament->setTurnIndex(index->turnIndex());
        dartsTournament->setRoundIndex(index->roundIndex());
        dartsTournament->setSetIndex(index->setIndex());
        dartsTournament->setAttemptIndex(index->attemptIndex());
    }
};

#endif // UPDATEDARTSINDEXES_H
