#ifndef DCUPDATESCOREMODELS_H
#define DCUPDATESCOREMODELS_H

#include "DartsController/DCScoresSLAs/idcupdatescoremodels.h"

class DCUpdateScoreModels : public IDCUpdateScoreModels
{
public:
    virtual void update(const QVector<DCContext::DCScoreModel> &scoreModels, IDCScoresService *scoresService) const override
    {
        updateModels(scoreModels,scoresService);
    }
private:
    void updateModels(const QVector<DCContext::DCScoreModel> &tuples, IDCScoresService *scoresService) const
    {
        for (const auto &scoreModel : tuples)
            updateTuple(scoreModel.playerId,scoreModel.totalScore,scoresService);
    }
    void updateTuple(const QUuid &id, const int &totalScore,IDCScoresService *scoresService) const
    {
        for (int i = 0; i < scoresService->scoreModels().count(); ++i) {
            auto scoreModel = scoresService->scoreModels().at(i);
            auto tId = scoreModel.playerId;
            if(tId == id)
                scoreModel.totalScore = totalScore;
            scoresService->scoreModels().replace(i,scoreModel);
        }
    }
};
#endif // DCREPLACETUPLES_H
