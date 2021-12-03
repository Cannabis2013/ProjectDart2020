#ifndef DCUPDATEINPUTDETAILS_H
#define DCUPDATEINPUTDETAILS_H
#include "DartsController/DCScoresSLAs/idcupdateplayerscores.h"
class DCUpdateInputDetails : public IDCUpdatePlayerScores
{
public:
    void update(const QVector<DCIptVals> &inputs, AbstractDCScoresCtx *scoreController) const override
    {
        for (const auto &input : inputs) {
            auto scoreModel = &scoreController->score(input.playerName);
            if(input.remainingScore < scoreModel->remainingScore)
                scoreModel->remainingScore = input.remainingScore;
        }
    }
private:
};
#endif // DPCSUBTRACTPLAYERSCORE_H
