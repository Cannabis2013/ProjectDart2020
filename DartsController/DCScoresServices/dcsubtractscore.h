#ifndef DCSUBTRACTSCORE_H
#define DCSUBTRACTSCORE_H

#include "DartsController/DCScoresSLAs/idcsubtractscore.h"
class DCSubtractScore : public IDCSubtractScore
{
public:
    virtual DCContext::DCScoreModel subtractScore(const DCInput &input, IDCScoresService *scoresService) const override
    {
        auto scoreModel = getTupleFromScoresService(input.playerId,scoresService);
        auto indexOfTuple = indexOf(scoreModel,scoresService);
        scoreModel.totalScore = subtract(scoreModel.totalScore, input.score);
        scoresService->scoreModels().replace(indexOfTuple, scoreModel);
        return scoreModel;
    }
private:
    DCContext::DCScoreModel getTupleFromScoresService(const QUuid& id, IDCScoresService *scoresService) const
    {
        auto scoreModels = scoresService->scoreModels();
        for (int i = 0; i < scoreModels.count(); ++i) {
            auto scoreModel = scoreModels.at(i);
            auto _id = scoreModel.playerId;
            if(id == _id)
                return scoreModel;
        }
        return DCContext::DCScoreModel();
    }
    int indexOf(const DCContext::DCScoreModel& tuple, IDCScoresService *scoresService) const
    {
        auto tuples = scoresService->scoreModels();
        for (int i = 0; i < tuples.count(); ++i) {
            auto t = tuples.at(i);
            if(t == tuple)
                return i;
        }
        return -1;
    }
    int subtract(const int &score, const int &candidate) const
    {
        return score - candidate;
    }
};
#endif // DCSUBTRACTSCORE_H
