#ifndef INPUTMODELSCOUNTSERVICE_H
#define INPUTMODELSCOUNTSERVICE_H

#include "idbcontext.h"
#include "icountinputmodels.h"
#include <iplayerinput.h>

class InputModelsCountService : public
        ICountInputModels
{
public:
    virtual int count(const QUuid &tournamentId, const IModelsDbContext *dbService) const override
    {
        auto models = getInputModels(tournamentId,dbService);
        return models.count();
    }
private:
    QVector<const IModel<QUuid>*> getInputModels(const QUuid &tournamentId, const IModelsDbContext *dbService) const
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
