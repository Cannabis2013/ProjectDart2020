#ifndef RESETDARTSTOURNAMENT_H
#define RESETDARTSTOURNAMENT_H
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
#include "DartsModelsContext/TournamentsSLAs/iresetdartstournament.h"
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
class ResetDartsTournament : public IResetDartsTournament
{
public:
    virtual IDartsDbContext *reset(const QUuid &tournamentId, IDartsDbContext *dbContext) const override
    {
        auto models = dbContext->models();
        auto dartsTournament = getModelById(tournamentId,models);
        resetDartsTournament(dartsTournament);
        resetWinnerDetails(dartsTournament);
        return dbContext;
    }
private:
    AbstractDartsTournament* getModelById(const QUuid &id, const QVector<IModel<QUuid>*> &models) const
    {
        for (auto &model : models) {
            if(model->id() == id)
                return dynamic_cast<AbstractDartsTournament*>(model);
        }
        return nullptr;
    }
    void resetWinnerDetails(ITournament *tournament) const
    {
        tournament->setWinnerId(QUuid());
        tournament->setWinnerName(QString());
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
#endif // RESETDARTSTOURNAMENT_H
