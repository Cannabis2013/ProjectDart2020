#ifndef DCUPDATESCOREMODELS_H
#define DCUPDATESCOREMODELS_H

#include "DartsController/DCScoresSLAs/idcupdatescoremodels.h"

class DCUpdateScoreModels : public IDCUpdateScoreModels
{
public:
    virtual void update(const QVector<DCScoreModel> &scoreModels, IDCScoresService *scoresService) const override
    {
        updateModels(scoreModels,scoresService);
    }
private:
    void updateModels(const QVector<DCScoreModel> &scoreModels, IDCScoresService *scoresService) const
    {
        for (const auto &scoreModel : scoreModels)
            updateScoreModel(scoreModel.playerId,scoreModel.remainingScore,scoresService);
    }
    void updateScoreModel(const QUuid &id, const int &remainingScore,IDCScoresService *scoresService) const
    {
        for (int i = 0; i < scoresService->scoreModels().count(); ++i) {
            auto scoreModel = scoresService->scoreModels().at(i);
            auto tId = scoreModel.playerId;
            if(tId == id)
                scoreModel.remainingScore = remainingScore;
            scoresService->scoreModels().replace(i,scoreModel);
        }
    }
};
#endif // DCREPLACETUPLES_H
