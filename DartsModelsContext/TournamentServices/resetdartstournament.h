#ifndef RESETDARTSTOURNAMENT_H
#define RESETDARTSTOURNAMENT_H
#include <qvector.h>
#include "DartsModelsContext/TournamentsSLAs/iresetdartstournament.h"
#include "DartsModelsContext/TournamentModelsSLAs/idartstournament.h"
#include "DartsModelsContext/DbSLAs/idbcontext.h"
class ResetDartsTournament : public IResetDartsTournament<IModel<QUuid>>
{
public:
    virtual IDbContext<BaseModel> *reset(const QUuid &tournamentId, IDbContext<BaseModel> *dbContext) const override
    {
        auto models = dbContext->models();
        auto dartsTournament = getModelById(tournamentId,models);
        resetDartsTournament(dartsTournament);
        resetWinnerDetails(dartsTournament);
        return dbContext;
    }
private:
    IDartsTournament* getModelById(const QUuid &id, const QVector<IModel<QUuid>*> &models) const
    {
        for (auto &model : models) {
            if(model->id() == id)
                return dynamic_cast<IDartsTournament*>(model);
        }
        return nullptr;
    }
    void resetWinnerDetails(IDartsTournament *tournament) const
    {
        tournament->setWinnerId(QUuid());
        tournament->setWinnerName(QString());
    }
    void resetDartsTournament(IDartsTournament *tournament) const
    {
        tournament->setTotalTurns(0);
        tournament->setTurnIndex(0);
        tournament->setRoundIndex(1);
        tournament->setSetIndex(0);
        tournament->setAttemptIndex(0);
    }
};
#endif // RESETDARTSTOURNAMENT_H
