#ifndef UPDATESCORERANGE_H
#define UPDATESCORERANGE_H

#include <DartsStatistics/Contracts/StatsServices/ScoreRange/iupdatescorerange.h>


struct PlayerStats;
struct SnapShot;

class UpdateScoreRange : public IUpdateScoreRange<SnapShot,PlayerStats>
{
public:
        virtual void update(SnapShot &snapShot, PlayerStats *stats) const override;
};

#endif // UPDATESCORERANGE_H
