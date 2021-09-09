#ifndef DCUPDATETUPLES_H
#define DCUPDATETUPLES_H

#include "idcupdatetuples.h"

class DCUpdateTuples : public IDCUpdateTuples
{
public:
    virtual void update(const QVector<DCContext::DCScoreModel> &tuples, IDCScoresService *scoresService) const override
    {
        updateTuples(tuples,scoresService);
    }
private:
    void updateTuples(const QVector<DCContext::DCScoreModel> &tuples, IDCScoresService *scoresService) const
    {
        for (const auto &tuple : tuples)
            updateTuple(tuple.id,tuple.totalScore,scoresService);
    }
    void updateTuple(const QUuid &id, const int &totalScore,IDCScoresService *scoresService) const
    {
        for (int i = 0; i < scoresService->scoreModels().count(); ++i) {
            auto tuple = scoresService->scoreModels().at(i);
            auto tId = tuple.id;
            if(tId == id)
                tuple.totalScore = totalScore;
            scoresService->scoreModels().replace(i,tuple);
        }
    }
};
#endif // DCREPLACETUPLES_H
