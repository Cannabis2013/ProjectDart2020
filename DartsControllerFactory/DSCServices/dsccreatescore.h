#ifndef DSCCREATESCORE_H
#define DSCCREATESCORE_H
#include "DCScoresSLAs/absdccreatescore.h"
#include <qvector.h>
class DSCCreateScore : public AbsDCCreateScore
{
public:
    virtual int calc(const int &scoreCandidate, const int &remScore) const override
    {
        return calcCandidate(remScore,scoreCandidate);
    }
private:
    int calcCandidate(const int &remScore, const int &scoreCandidate) const
    {
        auto totalScoreCandidate = remScore - scoreCandidate;
        if(totalScoreCandidate < 0)
            return remScore;
        return totalScoreCandidate;
    }
};
#endif // GETSCOREFROMDSCINPUT_H
