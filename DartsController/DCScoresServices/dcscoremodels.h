#ifndef DCSCOREMODELS_H
#define DCSCOREMODELS_H
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
class DCScoreModels : public IDCScoreModels
{
public:
    DartsScoreModels &scores() override
    {
        return _scoreModels;
    }
    DCScoreModel &score(const QUuid &playerId) override
    {
        for (auto &scoreModel : _scoreModels) {
            if(scoreModel.playerId == playerId)
                return scoreModel;
        }
        throw "SCOREMODEL NOT FOUND";
    }
    virtual void reset(const int &defaultScore) override
    {
        for (auto &scoreModel : _scoreModels)
            scoreModel.remainingScore = defaultScore;
    }
private:
    DartsScoreModels _scoreModels;
};
#endif // DARTSSCORES_H
