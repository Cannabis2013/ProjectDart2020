#ifndef RESETDARTSINDEXES_H
#define RESETDARTSINDEXES_H
#include "DartsModelsContext/IndexesSLAs/iresetdartsindexes.h"
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
class ResetDartsIndexes: public IResetDartsIndexes
{
public:
    IDartsDbContext *reset(const QUuid &id, IDartsDbContext *dbContext) const override
    {
        auto models = dbContext->models();
        auto model = getModelByTournamentId(id,models);
        if(model != nullptr)
            resetDartsTournament(dynamic_cast<AbstractDartsTournament*>(model));
        return dbContext;
    };
private:
    IModel<QUuid>* getModelByTournamentId(const QUuid &id,const QVector<IModel<QUuid>*> &models) const
    {
        for (const auto &model : models) {
            auto tournament = dynamic_cast<AbstractDartsTournament*>(model);
            if(tournament->id() == id)
                return tournament;
        }
        return nullptr;
    }
    void resetDartsTournament(AbstractDartsTournament *tournament) const
    {
        tournament->setTotalTurns(0);
        tournament->setTurnIndex(0);
        tournament->setRoundIndex(1);
        tournament->setSetIndex(0);
        tournament->setAttemptIndex(0);
    }
};
#endif // RESETDARTSINDEXES_H
