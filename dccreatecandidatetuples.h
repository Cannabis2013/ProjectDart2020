#ifndef DCCREATECANDIDATETUPLES_H
#define DCCREATECANDIDATETUPLES_H

#include "idartssubtractscores.h"

class DCCreateCandidateTuples : public IDCCreateCandidateTuples
{
public:
    virtual DCContext::DCPTuple getCandidate(const DCContext::IDCModel *model, IDCScoresService *scoresService) override
    {
        auto tuples = scoresService->tuples();
        auto tuple = this->tuple(model->playerId(),tuples);
        auto newScore = subtractScore(tuple.totalScore,model->score());
        return toTuple(tuple,newScore);
    }
    virtual QVector<DCContext::DCPTuple> getTupleCandidates(const QVector<DCContext::IDCModel *> &models, IDCScoresService *scoresService) override
    {
        QVector<DCContext::DCPTuple> candidates;
        for (const auto &model : models)
            candidates << getCandidate(model,scoresService);
        return candidates;
    }
private:
    DCContext::DCPTuple tuple(const QUuid &id, const QVector<DCContext::DCPTuple>& tuples) const
    {
        for (const auto &tuple : tuples) {
            if(tuple.id == id)
                return tuple;
        }
        return DCContext::DCPTuple();
    }
    int subtractScore(const int &score, const int &sub) const
    {
        if(score < sub)
            return score;
        return score - sub;
    }
    const DCContext::DCPTuple toTuple(const DCContext::DCPTuple t, const int &newScore) const
    {
        return DCContext::DCPTuple(t.id,t.name,newScore);
    }
};
#endif // DPCSUBTRACTPLAYERSCORE_H
