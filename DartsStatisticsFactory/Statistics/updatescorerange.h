#ifndef UPDATESCORERANGE_H
#define UPDATESCORERANGE_H
#include "StatsServices/ScoreRange/iupdatescorerange.h"
struct CurrentStat;
struct SnapShot;
class UpdateScoreRange : public IUpdateScoreRange<SnapShot,CurrentStat>
{
public:
    virtual void update(SnapShot &snapShot, CurrentStat *stats) const override;
};

#endif // UPDATESCORERANGE_H
