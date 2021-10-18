#ifndef GETSCOREFROMDSCINPUT_H
#define GETSCOREFROMDSCINPUT_H

#include "DartsController/DCScoresSLAs/idcgetscore.h"
class GetScoreFromDSCInput : public IDCGetScore
{
public:
    virtual int getScore(const DCInput &inputModel) const override
    {
        return inputModel.score;
    }
};
#endif // GETSCOREFROMDSCINPUT_H
