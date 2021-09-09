#ifndef GETSCOREFROMDSCINPUT_H
#define GETSCOREFROMDSCINPUT_H

#include "idcgetscore.h"
class GetScoreFromDSCInput : public IDCgetScore
{
public:
    virtual int getScore(const DCContext::IDCModel *inputModel) const override
    {
        return inputModel->score();
    }
};


#endif // GETSCOREFROMDSCINPUT_H
