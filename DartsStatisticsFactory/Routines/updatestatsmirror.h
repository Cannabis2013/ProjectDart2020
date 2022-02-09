#ifndef UPDATESTATSMIRROR_H
#define UPDATESTATSMIRROR_H
#include "Routines/IAddStatsToPlayer.h"

struct CurrentStat;
template<typename T, typename U> class IUpdateScoreRange;
template<typename T> class IStatsDb;
class ICalcAverage;
class IMirrorsDb;
class ServicesContext;
struct SnapShot;
class UpdateStatsMirror : public IAddStatsToPlayer<SnapShot>
{
public:
    typedef IStatsDb<CurrentStat> StatsDb;
    typedef IStatsDb<SnapShot> IptDb;
    typedef IUpdateScoreRange<SnapShot,CurrentStat> UpdateScoreRange;
    UpdateStatsMirror(ServicesContext *provider);
    virtual void update(Ipt &input) override;
    virtual void update(Ipts &inputs) override;
private:
    void upd(Ipt &input);
    void updateAccumulatedScore(const Ipt &input, CurrentStat *stats);
    StatsDb *_statsDb;
    ICalcAverage *_calcAvg;
    UpdateScoreRange *_updateScoreRange;
};

#endif // UPDATESTATSMIRROR_H
