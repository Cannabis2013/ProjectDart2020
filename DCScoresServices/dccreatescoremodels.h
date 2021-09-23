#ifndef DCCREATESCOREMODELS_H
#define DCCREATESCOREMODELS_H
#include "DCScoresSLAs/idccreatescoretuples.h"
class DCCreateScoreModels : public IDCCreateScoreTuples
{
public:
    virtual QVector<DCContext::DCScoreModel> createTuples(const PlayerModels &models, const int &initialScore) override
    {
        QVector<DCContext::DCScoreModel> tuples;
        for (const auto &model : models)
            tuples << createTuple(model,initialScore);
        return tuples;
    }
private:
    DCContext::DCScoreModel createTuple(const DCContext::IDCPlayer *playerModel, const int &initialScore) const
    {
        DCContext::DCScoreModel tuple;
        tuple.id = playerModel->playerId();
        tuple.name = playerModel->playerName();
        tuple.totalScore = initialScore;
        return tuple;
    }
};
#endif // DCCREATESCORETUPLES_H
