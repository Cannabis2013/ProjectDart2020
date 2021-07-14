#ifndef INPUTMODELSCOUNTSERVICE_H
#define INPUTMODELSCOUNTSERVICE_H

#include "imodelsdbcontext.h"
#include "icountinputmodels.h"
#include <iplayerinput.h>

namespace DartsModelsContext {
    class InputModelsCountService : public
            ICountInputModels
    {
    public:
        virtual int count(const QUuid &tournamentId, const IDartsInputDb *dbService) const override
        {
            auto models = getInputModels(tournamentId,dbService);
            return models.count();
        }
    private:
        QVector<const IPlayerInput*> getInputModels(const QUuid &tournamentId, const IDartsInputDb *dbService) const
        {
            auto models = dbService->models();
            QVector<const IPlayerInput*> tournamentInputs;
            for (const auto &model : models) {
                if(model->tournamentId() == tournamentId)
                    tournamentInputs << model;
            }
            return tournamentInputs;
        }
    };
}

#endif // INPUTMODELSCOUNTSERVICE_H
