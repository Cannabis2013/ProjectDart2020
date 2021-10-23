#ifndef DCSCORESSERVICE_H
#define DCSCORESSERVICE_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"

class DCScoresService : public IDCScoresService
{
public:
    DartsScoreModels &scoreModels() override
    {
        return _scoreModels;
    }
    DCScoreModel scoreModel(const QUuid &playerId) const override
    {
        return getScoreModelById(playerId);
    }
    DCScoreModel subtractAndUpdate(const DCInput &input) override
    {
        auto scoreModel = getScoreModelById(input.playerId);
        auto newRemainingScore = scoreModel.remainingScore - input.score;
        scoreModel.remainingScore = newRemainingScore;
        auto index = _scoreModels.indexOf(scoreModel);
        _scoreModels.replace(index,scoreModel);
        return scoreModel;
    }
    virtual DCScoreModel addAndUpdate(const DCInput &input) override
    {
        auto scoreModel = getScoreModelById(input.playerId);
        auto newRemainingScore = scoreModel.remainingScore + input.score;
        scoreModel.remainingScore = newRemainingScore;
        auto index = _scoreModels.indexOf(scoreModel);
        _scoreModels.replace(index,scoreModel);
        return scoreModel;
    }
    virtual void updatePlayerRemainingScore(const DCInput &input) override
    {
        auto scoreModel = getScoreModelById(input.playerId);
        scoreModel.remainingScore = input.remainingScore;
        auto index = _scoreModels.indexOf(scoreModel);
        _scoreModels.replace(index,scoreModel);
    }
private:
    DCScoreModel getScoreModelById(const QUuid &playerId) const
    {
        for (const auto &scoreModel : _scoreModels) {
            if(scoreModel.playerId == playerId)
                return scoreModel;
        }
        return DCScoreModel();
    }
    DartsScoreModels _scoreModels;
};
#endif // DARTSSCORES_H
