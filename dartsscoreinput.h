#ifndef DARTSSCORE_H
#define DARTSSCORE_H

#include <quuid.h>
#include "idartsscoreinput.h"

class DartsScoreInput : public IDartsScoreInput<QUuid>
{
public:
    virtual int accumulatedScore() const override
    {
        return _accumulatedScore;
    }
    virtual DartsScoreInput *setAccumulatedScore(const int& score) override
    {
        _accumulatedScore = score;
        return this;
    }
private:
    int _accumulatedScore;
};

#endif // DARTSSCORE_H
