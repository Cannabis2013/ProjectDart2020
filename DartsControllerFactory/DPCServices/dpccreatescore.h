#ifndef DPCCREATESCORE_H
#define DPCCREATESCORE_H
#include "DCScoresSLAs/absdccreatescore.h"
#include <qvector.h>
class DPCCreateScore : public AbsDCCreateScore
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
#endif // POINTSCORECALCULATOR_H
