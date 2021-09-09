#ifndef DCADDSCORE_H
#define DCADDSCORE_H

#include "idcaddscore.h"

class DCAddScore : public IDCAddScore
{
public:
    virtual DCContext::DCScoreModel addPlayerScore(const DCContext::IDCModel *model, IDCScoresService *scoresService) const override
    {
        auto tuple = getTupleFromScoresService(model->playerId(),scoresService);
        auto indexOfTuple = indexOf(tuple,scoresService);
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
    DCContext::DCScoreModel getTupleFromScoresService(const QUuid& id, IDCScoresService *scoresService) const
    {
        auto tuples = scoresService->scoreModels();
        for (int i = 0; i < tuples.count(); ++i) {
            auto tuple = tuples.at(i);
            auto _id = tuple.id;
            if(id == _id)
                return tuple;
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
    int sum(const int &score, const int &newSum) const
    {
        return score + newSum;
    }
};
#endif // DARTSADDSCORE_H
