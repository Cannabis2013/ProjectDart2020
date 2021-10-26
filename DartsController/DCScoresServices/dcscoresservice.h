#ifndef DCSCORESSERVICE_H
#define DCSCORESSERVICE_H
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
class DCScoresService : public IDCScoreModels
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
private:
    DartsScoreModels _scoreModels;
};
#endif // DARTSSCORES_H
