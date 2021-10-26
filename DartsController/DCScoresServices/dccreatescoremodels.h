#ifndef DCCREATESCOREMODELS_H
#define DCCREATESCOREMODELS_H
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
class DCCreateScoreModels : public IDCScoreBuilder
{
public:
    virtual QVector<DCScoreModel> createScores(const QVector<DCPlayer> &models, const int &initialScore) override
    {
        QVector<DCScoreModel> scoreModels;
        for (const auto &model : models)
            scoreModels << toModel(model,initialScore);
        return scoreModels;
    }
private:
    DCScoreModel toModel(const DCPlayer &playerModel, const int &initialScore) const
    {
        DCScoreModel scoreModel;
        scoreModel.playerId = playerModel.id;
        scoreModel.playerName = playerModel.name;
        scoreModel.remainingScore = initialScore;
        return scoreModel;
    }
};
#endif // DCCREATESCORETUPLES_H
