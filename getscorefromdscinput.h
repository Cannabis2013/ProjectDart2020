#ifndef GETSCOREFROMDSCINPUT_H
#define GETSCOREFROMDSCINPUT_H

#include "idcgetscore.h"
class GetScoreFromDSCInput : public IDCgetScore
{
public:
    virtual int getScore(const DCContext::IDCInputModel *inputModel) const override
    {
        return inputModel->score();
    }
};


#endif // GETSCOREFROMDSCINPUT_H
