#ifndef DCCREATESCORETUPLES_H
#define DCCREATESCORETUPLES_H
#include <idccreatescoretuples.h>
class DCCreateScoreTuples : public IDCCreateScoreTuples
{
public:
    virtual QVector<DCContext::DCScoreModel> createTuples(const PlayerModels &models, const IDartsMetaData *dartsMeta) override
    {
        QVector<DCContext::DCScoreModel> tuples;
        for (const auto &model : models)
            tuples << createTuple(model,dartsMeta->initialScore());
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
