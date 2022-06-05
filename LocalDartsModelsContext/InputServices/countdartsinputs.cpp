#include "countdartsinputs.h"

#include <DartsModelsContext/DbSLAs/idbcontext.h>

#include <DartsModelsContext/InputModelsSLAs/iplayerinput.h>

int CountDartsInputs::count(const QUuid &tournamentId, const DbCtx *dbService) const
{
        auto models = getInputModels(tournamentId,dbService);
        return models.count();
}

QVector<const IModel<QUuid> *> CountDartsInputs::getInputModels(const QUuid &tournamentId, const DbCtx *dbService) const
{
        auto models = dbService->models();
        QVector<const IModel<QUuid>*> tournamentInputs;
        for (const auto &model : qAsConst(models)) {
                auto inputModel = dynamic_cast<const IPlayerInput*>(model);
                if(inputModel->tournamentId() == tournamentId)
                        tournamentInputs << model;
        }
        return tournamentInputs;
}
