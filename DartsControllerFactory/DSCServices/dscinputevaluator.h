#ifndef DSCINPUTEVALUATOR_H
#define DSCINPUTEVALUATOR_H
#include "DCInputSLAs/idcipteval.h"
#include <Models/dcinput.h>
#include "Models/dcmeta.h"
class DSCInputEvaluator : public IDCIptEval
{
public:
    virtual void eval(DCInput &input, const int &scoreCand, DCMeta &meta,
                      const DCPlayer &, const int &winnerStatus) override
    {
        if(scoreCand >= minimumAllowedScore)
        {
            input.approved = true;
            input.remScore = scoreCand;
        }
        else if(scoreCand == 0)
        {
            input.approved = true;
            input.remScore = 0;
            updateWinnerMeta(input,meta,winnerStatus);
        }
        else
        {
            input.score = 0;
        }
    }
private:
    void updateWinnerMeta(DCInput &input, DCMeta &meta, const int &winnerStatus) const
    {
        meta.winnerName = input.playerName;
        meta.status = winnerStatus;
    }
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
