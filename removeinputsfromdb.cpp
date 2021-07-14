#include "removeinputsfromdb.h"

void DartsModelsContext::RemoveInputsFromDb::remove(const QVector<const IPlayerInput*> &models,
                                                                   const int &hint,
                                                                   IDartsInputDb *dbService) const
{
    for (const auto model : qAsConst(models))
    {
        if(model->hint() == hint)
        {
            remove(model->id(),dbService);
            return;
        }
    }
}


void DartsModelsContext::RemoveInputsFromDb::remove(const QUuid &id, IDartsInputDb *dbService) const
{
    auto models = dbService->models();
    for (int i = 0; i < models.count(); ++i) {
        auto model = models.at(i);
        if(model->id() == id)
        {
            dbService->remove(i);
            return;
        }
    }
}


void DartsModelsContext::RemoveInputsFromDb::remove(const QVector<const IPlayerInput*> &models,
                                                                   const QUuid &tournamentId,
                                                                   IDartsInputDb *dbService) const
{
    for (const auto& model : models) {
        if(model->tournamentId() == tournamentId)
            remove(model->id(),dbService);
    }
}
