#ifndef DCCREATECANDIDATEMODELS_H
#define DCCREATECANDIDATEMODELS_H

#include "DartsController/DCScoresSLAs/idccreatecandidatemodels.h"

class DCCreateCandidateModels : public IDCCreateCandidateModels
{
public:
    virtual DCContext::DCScoreModel getCandidate(const DCContext::IDCInputModel *model, IDCScoresService *scoresService) override
    {
        auto tuples = scoresService->scoreModels();
        auto tuple = this->tuple(model->playerId(),tuples);
        auto newScore = subtractScore(tuple.totalScore,model->score());
        return toTuple(tuple,newScore);
    }
    virtual QVector<DCContext::DCScoreModel> getScoreCandidates(const QVector<DCContext::IDCInputModel *> &models, IDCScoresService *scoresService) override
    {
        auto scoreModels = scoresService->scoreModels();
        for (auto &model : scoreModels)
        {
            auto initialScore = model.totalScore;
            auto playerScore = sum(model.id,models);
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
    DCContext::DCScoreModel tuple(const QUuid &id, const QVector<DCContext::DCScoreModel>& tuples) const
    {
        for (const auto &tuple : tuples) {
            if(tuple.id == id)
                return tuple;
        }
        return DCContext::DCScoreModel();
    }
    int subtractScore(const int &score, const int &sub) const
    {
        if(score < sub)
            return score;
        return score - sub;
    }
    const DCContext::DCScoreModel toTuple(const DCContext::DCScoreModel t, const int &newScore) const
    {
        return DCContext::DCScoreModel(t.id,t.name,newScore);
    }
};
#endif // DPCSUBTRACTPLAYERSCORE_H
