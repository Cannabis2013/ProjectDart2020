#include "removedartsinputs.h"
#include <qvector.h>
#include <quuid.h>
#include <DartsModelsContext/Contracts/Db/idbcontext.h>
#include <DartsModelsContext/Contracts/Input/iplayerinput.h>

void RemoveDartsInputs::removeInputsById(const QUuid &id, DbContext *dbContext) const
{
    auto models = dbContext->models();
    for (const auto &model : qAsConst(models))
        removeModel(model,id,dbContext);
}

void RemoveDartsInputs::removeInputsByTournamentId(const QUuid &tournamentId, DbContext *dbContext) const
{
    auto models = dbContext->models();
    for (const auto& model : qAsConst(models))
    {
        auto inputModel = dynamic_cast<IPlayerInput*>(model);
        if(inputModel->tournamentId() == tournamentId)
            removeModel(model,model->id(),dbContext);
    }
}

void RemoveDartsInputs::removeByTournamentIds(const QVector<QUuid> &tournamentIds, DbContext *dbContext) const
{
    for (const auto &tournamentId : tournamentIds)
        removeInputsByTournamentId(tournamentId,dbContext);
}

void RemoveDartsInputs::removeHidden(const QUuid &tournamentId, DbContext *dbContext) const
{
    auto models = dbContext->models();
    for (const auto &model : qAsConst(models))
        removeModel(model,tournamentId,HiddenHint,dbContext);
}

void RemoveDartsInputs::removeDisplayed(const QUuid &tournamentId, DbContext *dbContext) const
{
    auto models = dbContext->models();
    for (const auto &model : qAsConst(models))
        removeModel(model,tournamentId,DisplayHint,dbContext);
}

void RemoveDartsInputs::removeModel(IModel<QUuid> *model, const QUuid &tournamentId, const int &hint, DbContext *dbContext) const
{
    auto input = dynamic_cast<const IPlayerInput*>(model);
    if(input->hint() == hint && input->tournamentId() == tournamentId)
        removeModel(model,input->id(),dbContext);
}

bool RemoveDartsInputs::removeModel(IModel<QUuid> *inputModel, const QUuid &id, DbContext *dbContext) const
{
    if(inputModel->id() == id)
    {
        dbContext->remove(dbContext->indexOf(inputModel));
        return true;
    }
    return false;
}
