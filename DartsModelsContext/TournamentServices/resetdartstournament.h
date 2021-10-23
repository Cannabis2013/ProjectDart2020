#ifndef RESETDARTSTOURNAMENT_H
#define RESETDARTSTOURNAMENT_H
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
#include "DartsModelsContext/TournamentsSLAs/iresetdartstournament.h"
class ResetDartsTournament : public IResetDartsTournament
{
public:
    virtual IDartsDbContext *reset(const QUuid &tournamentId, IDartsDbContext *dbContext) const override
    {
        auto models = dbContext->models();
        auto tournamentById = dynamic_cast<ITournament*>(getModelById(tournamentId,models));
        resetWinnerDetails(tournamentById);
        return dbContext;
    }
private:
    IModel<QUuid>* getModelById(const QUuid &id, const QVector<IModel<QUuid>*> &models) const
    {
        for (auto &model : models) {
            if(model->id() == id)
                return model;
        }
        return nullptr;
    }
    void resetWinnerDetails(ITournament *tournament) const
    {
        tournament->setWinnerId(QUuid());
        tournament->setWinnerName(QString());
    }
};
#endif // RESETDARTSTOURNAMENT_H
