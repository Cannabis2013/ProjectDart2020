#ifndef DARTSPOINTFILTERSERVICE_H
#define DARTSPOINTFILTERSERVICE_H

#include "igetdartspointbyparameters.h"

class GetDartsPointByParameters : public IGetDartsPointByParameters
{
    // IDartsPointModelsFilterService interface
public:
    const DartsModelsContext::IDartsPointInput* getModelByParameters(const IDartsPointDb* dbService,
                                                 const QUuid &tournamentId,
                                                 const QUuid &playerId,
                                                 const int &round,
                                                 const int &attempt) const override
    {
        QVector<const DartsModelsContext::IDartsPointInput*> filteredModels = dbService->dartsInputModels();
        filteredModels = filterByTournamentId(filteredModels,tournamentId);
        filteredModels = filterByPlayerId(filteredModels,playerId);
        filteredModels = filterByRound(filteredModels,round);
        auto model = getModelByAttempt(filteredModels,attempt);
        return model;
    }
private:
    QVector<const DartsModelsContext::IDartsPointInput*> filterByTournamentId(const QVector<const DartsModelsContext::IDartsPointInput*>& models,
                                                          const QUuid& tournamentId) const
    {
        QVector<const DartsModelsContext::IDartsPointInput*> filteredModels;
        for (const auto& model : models) {
            if(model->tournamentId() == tournamentId)
                filteredModels << model;
        }
        return filteredModels;
    }
    QVector<const DartsModelsContext::IDartsPointInput*> filterByPlayerId(const QVector<const DartsModelsContext::IDartsPointInput*>& models,
                                                      const QUuid& playerId) const
    {
        QVector<const DartsModelsContext::IDartsPointInput*> filteredModels;
        for (const auto& model : models) {
            if(model->playerId() == playerId)
                filteredModels << model;
        }
        return filteredModels;
    }
    QVector<const DartsModelsContext::IDartsPointInput*> filterByRound(const QVector<const DartsModelsContext::IDartsPointInput*>& models,
                                                   const int& round) const
    {
        QVector<const DartsModelsContext::IDartsPointInput*> filteredModels;
        for (const auto& model : models) {
            if(model->roundIndex() == round)
                filteredModels << model;
        }
        return filteredModels;
    }
    const DartsModelsContext::IDartsPointInput* getModelByAttempt(const QVector<const DartsModelsContext::IDartsPointInput*>& models,
                                                     const int& attempt) const
    {
        QVector<const DartsModelsContext::IDartsPointInput*> filteredModels;
        for (const auto& model : models) {
            if(model->attempt() == attempt)
                return model;
        }
        return nullptr;
    }
};

#endif // DARTSPOINTFILTERSERVICE_H
