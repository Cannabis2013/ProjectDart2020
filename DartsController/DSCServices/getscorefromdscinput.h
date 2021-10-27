#ifndef GETSCOREFROMDSCINPUT_H
#define GETSCOREFROMDSCINPUT_H

#include "DartsController/DCScoresSLAs/idccalcscore.h"
class GetScoreFromDSCInput : public IDCCalcScore
{
public:
    virtual int getScore(const DCInput &inputModel) const override
    {
        return inputModel.score;
    }
};
#endif // GETSCOREFROMDSCINPUT_H
