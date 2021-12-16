#ifndef COUNTDARTSINPUTS_H
#define COUNTDARTSINPUTS_H
#include "DartsModelsContext/InputSLAs/icountinputmodels.h"
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include <qvector.h>
#include "DartsModelsContext/DbSLAs/idbcontext.h"
#include <quuid.h>
class CountDartsInputs : public ICountInputModels<IDbContext<IModel<QUuid>>>
{
public:
    virtual int count(const QUuid &tournamentId, const DbCtx *dbService) const override
    {
        auto models = getInputModels(tournamentId,dbService);
        return models.count();
    }
private:
    QVector<const IModel<QUuid>*> getInputModels(const QUuid &tournamentId, const DbCtx *dbService) const
    {
        auto models = dbService->models();
        QVector<const IModel<QUuid>*> tournamentInputs;
        for (const auto &model : models) {
            auto inputModel = dynamic_cast<const IPlayerInput*>(model);
            if(inputModel->tournamentId() == tournamentId)
                tournamentInputs << model;
        }
        return tournamentInputs;
    }
};
#endif // INPUTMODELSCOUNTSERVICE_H
