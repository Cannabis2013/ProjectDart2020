#ifndef DPCSUBTRACTPLAYERSCORE_H
#define DPCSUBTRACTPLAYERSCORE_H

#include "idpccalcscorecandidate.h"

class DPCSubtractScore : public IDPCCalcScoreCandidate
{
    // IDPCSubtractScore interface
public:
    virtual int getTotalScoreCandidate(const DPCContext::IDPCModel *model, IDCScoresService *scoresService) override
    {
        auto tuples = scoresService->tuples();
        auto tuple = this->tuple(model->playerId(),tuples);
        auto subtractedScore = subtractScore(tuple.totalScore,model->score());
        return subtractedScore;
    }
    virtual QVector<int> getTotalScoreCandidate(const QVector<DPCContext::IDPCModel *> &models, IDCScoresService *scoresService) override
    {
        QVector<int> candidates;
        for (const auto &model : models)
            candidates << getTotalScoreCandidate(model,scoresService);
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
};

#endif // DPCSUBTRACTPLAYERSCORE_H
