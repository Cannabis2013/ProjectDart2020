#ifndef UPDATEPLAYERSTATS_H
#define UPDATEPLAYERSTATS_H
#include "Routines/IAddStatsToPlayer.h"
template<typename T, typename U> class IUpdateScoreRange;
template<typename T> class IStatsDb;
class ICalcAverage;
class CurrentStats;
class ServicesContext;
struct Input;
class UpdatePlayerStats : public IAddStatsToPlayer<Input>
{
public:
    typedef IStatsDb<CurrentStats> StatsDb;
    typedef IStatsDb<Input> IptDb;
    typedef IUpdateScoreRange<Input,CurrentStats> UpdateScoreRange;
    UpdatePlayerStats(ServicesContext *provider);
    virtual void update(Ipt &input) override;
    virtual void update(Ipts &inputs) override;
private:
    void upd(Ipt &input);
    void updateAccumulatedScore(const Ipt &input, CurrentStats *stats);
    StatsDb *_statsDb;
    ICalcAverage *_calcAvg;
    UpdateScoreRange *_updateScoreRange;
};

#endif // UPDATEPLAYERSTATS_H
