#ifndef GETDARTSSCOREBYPARAMETERS_H
#define GETDARTSSCOREBYPARAMETERS_H

#include "igetdartsscorebyparameters.h"

class GetDartsScoreByParameters : public IGetDartsScoreByParameters
{
    // IDartsPointModelsFilterService interface
public:
    const IDartsScoreInput* getModelByParameters(const IDartsScoreDb* dbService,
                                                 const QUuid &tournamentId,
                                                 const QUuid &playerId,
                                                 const int &round) const override
    {
        QVector<const IDartsScoreInput*> filteredModels = dbService->dartsScoreModels();
        filteredModels = filterByTournamentId(filteredModels,tournamentId);
        filteredModels = filterByPlayerId(filteredModels,playerId);
        auto model = getModelByRound(filteredModels,round);
        return model;
    }
private:
    QVector<const IDartsScoreInput*> filterByTournamentId(const QVector<const IDartsScoreInput*>& models,
                                                          const QUuid& tournamentId) const
    {
        QVector<const IDartsScoreInput*> filteredModels;
        for (const auto& model : models) {
            if(model->tournamentId() == tournamentId)
                filteredModels << model;
        }
        return filteredModels;
    }
    QVector<const IDartsScoreInput*> filterByPlayerId(const QVector<const IDartsScoreInput*>& models,
                                                      const QUuid& playerId) const
    {
        QVector<const IDartsScoreInput*> filteredModels;
        for (const auto& model : models) {
            if(model->playerId() == playerId)
                filteredModels << model;
        }
        return filteredModels;
    }
    const IDartsScoreInput* getModelByRound(const QVector<const IDartsScoreInput*>& models,
                                          const int& round) const
    {
        for (const auto& model : models) {
            if(model->roundIndex() == round)
                return model;
        }
        return nullptr;
    }
};

#endif // GETDARTSSCOREBYPARAMETERS_H
