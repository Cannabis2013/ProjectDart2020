#ifndef GETDARTSINPUTMODELS_H
#define GETDARTSINPUTMODELS_H

#include "DartsModelsContext/InputsDbSLAs/igetinputmodelsservice.h"
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include "ModelsContext/DbSLAs/idbcontext.h"

class GetDartsInputModels : public IGetInputModelsService
{
public:
    QVector<IModel<QUuid> *> get(const QUuid &tournamentId, const IModelsDbContext *dbService) const override
    {
        const auto& models = dbService->models();
        auto tournamentInputs = getModels(tournamentId,models);
        return tournamentInputs;
    }
    QVector<IModel<QUuid>*> get(const QUuid &tournamentId, const int &hint, const IModelsDbContext *dbService) const override
    {
        auto models = get(tournamentId,dbService);
        auto tournamentInputs = getModels(tournamentId,models);
        auto inputsByHint = getModels(hint,tournamentInputs);
        return inputsByHint;
    }
private:
    QVector<IModel<QUuid>*> getModels(const QUuid &tournamentId, const QVector<IModel<QUuid> *> &models) const
    {
        QVector<IModel<QUuid>*> list;
        for (const auto& model : models) {
            auto inputModel = dynamic_cast<IPlayerInput*>(model);
            if(inputModel->tournamentId() == tournamentId)
                list << model;
        }
        return list;
    }
    QVector<IModel<QUuid>*> getModels(const int &hint, const QVector<IModel<QUuid> *> &models) const
    {
        QVector<IModel<QUuid>*> list;
        for (const auto& model : models) {
            auto inputModel = dynamic_cast<IPlayerInput*>(model);
            if(inputModel->hint() == hint)
                list << model;
        }
        return list;
    }
};
#endif // GETINPUTMODELSSERVICE_H
