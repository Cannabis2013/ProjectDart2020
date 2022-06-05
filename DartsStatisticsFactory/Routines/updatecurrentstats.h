#ifndef UPDATESTATSMIRROR_H
#define UPDATECURRENTSTATS_H

#include <DartsStatistics/Routines/IUpdateCurrentStats.h>

struct CurrentStat;
template<typename T, typename U> class IUpdateScoreRange;
template<typename T> class IStatsDb;
class ICalcAverage;
class IMirrorsDb;
class ServicesContext;
struct SnapShot;

class UpdateCurrentStats : public IUpdateCurrentStats<SnapShot>
{
public:
        typedef IStatsDb<CurrentStat> StatsDb;
        typedef IStatsDb<SnapShot> IptDb;
        typedef IUpdateScoreRange<SnapShot,CurrentStat> UpdateScoreRange;
        UpdateCurrentStats(ServicesContext *provider);
        virtual void update(Ipt &input) override;
        virtual void update(Inputs &inputs) override;
private:
        void upd(Ipt &input);
        void updateAccumulatedScore(const Ipt &input, CurrentStat *stats);
        StatsDb *_statsDb;
        ICalcAverage *_calcAvg;
        UpdateScoreRange *_updateScoreRange;
};

#endif // UPDATESTATSMIRROR_H
