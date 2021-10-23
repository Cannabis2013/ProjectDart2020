#ifndef DCUPDATEINPUTDETAILS_H
#define DCUPDATEINPUTDETAILS_H
#include "DartsController/DCScoresSLAs/idcupdateinputdetails.h"

class DCUpdateInputDetails : public IDCUpdateInputDetails
{
public:
    void update(const QVector<DCInput> &inputs, IDCScoreStats *statsController,
                IDCScoresService *scoreController) override
    {
        for (const auto &input : inputs) {
            auto scoreModel = scoreController->scoreModel(input.playerId);
            if(input.remainingScore < scoreModel.remainingScore)
                scoreController->updatePlayerRemainingScore(input);
            statsController->updatePlayerStat(input);
        }
    }
private:
};
#endif // DPCSUBTRACTPLAYERSCORE_H
