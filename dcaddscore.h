#ifndef DCADDSCORE_H
#define DCADDSCORE_H

#include "idcaddscore.h"

class DCAddScore : public IDCAddScore
{
public:
    virtual DCContext::DCScoreModel addPlayerScore(const DCContext::IDCInputModel *model, IDCScoresService *scoresService) const override
    {
        auto scoreModels = scoresService->scoreModels();
        auto tuple = getTupleFromScoresService(model->playerId(),scoreModels);
        auto indexOfTuple = indexOf(tuple,scoreModels);
        updateTuple(tuple,sum(tuple.totalScore,model->score()));
        scoresService->scoreModels().replace(indexOfTuple, tuple);
        return tuple;
    }
private:
    void updateTuple(DCContext::DCScoreModel &tuple, const int &score) const
    {
        if(score < 0)
            throw "Invalid score";
        tuple.totalScore = score;
    }
    DCContext::DCScoreModel getTupleFromScoresService(const QUuid& id, const IDCScoresService::DartsScoreModels &scoreModels) const
    {
        for (int i = 0; i < scoreModels.count(); ++i) {
            auto scoreModel = scoreModels.at(i);
            auto _id = scoreModel.id;
            if(id == _id)
                return scoreModel;
        }
        return DCContext::DCScoreModel();
    }
    int indexOf(const DCContext::DCScoreModel& scoreModel, const IDCScoresService::DartsScoreModels &scoreModels) const
    {
        for (int i = 0; i < scoreModels.count(); ++i) {
            auto t = scoreModels.at(i);
            if(t == scoreModel)
                return i;
        }
        return -1;
    }
    int sum(const int &score, const int &newSum) const
    {
        return score + newSum;
    }
};
#endif // DARTSADDSCORE_H
