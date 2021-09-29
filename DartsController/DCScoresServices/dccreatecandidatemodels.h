#ifndef DCCREATECANDIDATEMODELS_H
#define DCCREATECANDIDATEMODELS_H

#include "DartsController/DCScoresSLAs/idccreatecandidatemodels.h"

class DCCreateCandidateModels : public IDCCreateCandidateModels
{
public:
    virtual DCContext::DCScoreModel getCandidate(const DCContext::IDCInputModel *model, IDCScoresService *scoresService) override
    {
        auto tuples = scoresService->scoreModels();
        auto tuple = this->scoreModel(model->playerId(),tuples);
        auto newScore = subtractScore(tuple.totalScore,model->score());
        return toModel(tuple,newScore);
    }
    virtual QVector<DCContext::DCScoreModel> getScoreCandidates(const QVector<DCContext::IDCInputModel *> &models, IDCScoresService *scoresService) override
    {
        auto scoreModels = scoresService->scoreModels();
        for (auto &model : scoreModels)
        {
            auto initialScore = model.totalScore;
            auto playerScore = sum(model.playerId,models);
            auto result = subtractScore(initialScore,playerScore);
            model.totalScore = result;
        }
        return scoreModels;
    }
private:
    int sum(const QUuid &id, const QVector<DCContext::IDCInputModel*> &models) const
    {
        auto s = 0;
        for (const auto &model : models) {
            if(model->playerId() == id)
                s += model->score();
        }
        return s;
    }
    DCContext::DCScoreModel scoreModel(const QUuid &id, const QVector<DCContext::DCScoreModel>& tuples) const
    {
        for (const auto &scoreModel : tuples) {
            if(scoreModel.playerId == id)
                return scoreModel;
        }
        return DCContext::DCScoreModel();
    }
    int subtractScore(const int &score, const int &sub) const
    {
        if(score < sub)
            return score;
        return score - sub;
    }
    const DCContext::DCScoreModel toModel(const DCContext::DCScoreModel t, const int &newScore) const
    {
        return DCContext::DCScoreModel(t.playerId,t.playerName,newScore);
    }
};
#endif // DPCSUBTRACTPLAYERSCORE_H
