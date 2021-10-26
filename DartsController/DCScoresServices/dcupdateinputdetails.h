#ifndef DCUPDATEINPUTDETAILS_H
#define DCUPDATEINPUTDETAILS_H

#include "DartsController/DCScoresSLAs/idcupdateinputdetails.h"

class DCUpdateInputDetails : public IDCUpdateInputDetails
{
public:
    void update(const QVector<DCInput> &inputs, IDCScoreModels *scoreController) override
    {
        for (const auto &input : inputs) {
            auto scoreModel = &scoreController->score(input.playerId);
            if(input.remainingScore < scoreModel->remainingScore)
                scoreModel->remainingScore = input.remainingScore;
        }
    }
private:
};
#endif // DPCSUBTRACTPLAYERSCORE_H
