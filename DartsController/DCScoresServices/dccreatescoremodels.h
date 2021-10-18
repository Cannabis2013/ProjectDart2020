#ifndef DCCREATESCOREMODELS_H
#define DCCREATESCOREMODELS_H
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
class DCCreateScoreModels : public IDCScoreBuilder
{
public:
    virtual QVector<DCContext::DCScoreModel> buildScores(const QVector<DCPlayer> &models, const int &initialScore) override
    {
        QVector<DCContext::DCScoreModel> tuples;
        for (const auto &model : models)
            tuples << toModel(model,initialScore);
        return tuples;
    }
private:
    DCContext::DCScoreModel toModel(const DCPlayer &playerModel, const int &initialScore) const
    {
        DCContext::DCScoreModel tuple;
        tuple.playerId = playerModel.id;
        tuple.playerName = playerModel.name;
        tuple.totalScore = initialScore;
        return tuple;
    }
};
#endif // DCCREATESCORETUPLES_H
