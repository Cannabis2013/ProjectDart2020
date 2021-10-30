#ifndef DCINITIALSCORE_H
#define DCINITIALSCORE_H

#include "DartsController/DCMetaSLAs/idcinitialscore.h"

class DCInitialScore : public IDCInitialScore
{
public:
    static DCInitialScore *createInstance(const int &value)
    {
        return new DCInitialScore(value);
    }
    virtual int get() const override
    {
        return _initialScore;
    }
private:
    DCInitialScore(const int &value):
        _initialScore(value){}
    const int _initialScore;
};
#endif // DARTSMETADATASERVICE_H
