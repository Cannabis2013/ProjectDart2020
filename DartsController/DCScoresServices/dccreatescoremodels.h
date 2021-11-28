#ifndef DCCREATESCOREMODELS_H
#define DCCREATESCOREMODELS_H
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
class DCCreateScoreModels : public IDCScoreBuilder
{
public:
    virtual QVector<DCScoreModel> createScores(const Players &players, const int &initialScore) const override
    {
        QVector<DCScoreModel> scoreModels;
        for (const auto &player : players)
            scoreModels << toModel(player,initialScore);
        return scoreModels;
    }
private:
    DCScoreModel toModel(const Player *player, const int &initialScore) const
    {
        DCScoreModel scoreModel;
        scoreModel.playerId = player->id();
        scoreModel.playerName = player->name();
        scoreModel.remainingScore = initialScore;
        return scoreModel;
    }
};
#endif // DCCREATESCORETUPLES_H
