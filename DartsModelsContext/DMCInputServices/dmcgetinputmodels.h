#ifndef DMCGETINPUTMODELS_H
#define DMCGETINPUTMODELS_H

#include "DartsModelsContext/DMCInputSLAs/igetinputmodelsservice.h"
#include "DartsModelsContext/DMCInputSLAs/iplayerinput.h"
#include "ModelsContext/MCDbSLAs/idbcontext.h"

class DMCGetInputModels : public IGetInputModelsService
{
public:
    QVector<const IModel<QUuid> *> inputModels(const QUuid &tournamentId, const IModelsDbContext *dbService) const override
    {
        const auto& models = dbService->models();
        auto tournamentInputs = getModels(tournamentId,models);
        return tournamentInputs;
    }
    QVector<const IModel<QUuid>*> inputModels(const QUuid &tournamentId, const int &hint, const IModelsDbContext *dbService) const override
    {
        auto models = inputModels(tournamentId,dbService);
        auto tournamentInputs = getModels(tournamentId,models);
        auto inputsByHint = getModels(hint,tournamentInputs);
        return inputsByHint;
    }
private:
    QVector<const IModel<QUuid>*> getModels(const QUuid &tournamentId, const QVector<const IModel<QUuid> *> &models) const
    {
        QVector<const IModel<QUuid>*> list;
        for (const auto& model : models) {
            auto inputModel = dynamic_cast<const IPlayerInput*>(model);
            if(inputModel->tournamentId() == tournamentId)
                list << model;
        }
        return list;
    }
    QVector<const IModel<QUuid>*> getModels(const int &hint, const QVector<const IModel<QUuid> *> &models) const
    {
        QVector<const IModel<QUuid>*> list;
        for (const auto& model : models) {
            auto inputModel = dynamic_cast<const IPlayerInput*>(model);
            if(inputModel->hint() == hint)
                list << model;
        }
        return list;
    }
};
#endif // GETINPUTMODELSSERVICE_H
