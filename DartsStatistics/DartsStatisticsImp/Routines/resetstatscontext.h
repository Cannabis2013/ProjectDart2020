#ifndef RESETSTATSCONTEXT_H
#define RESETSTATSCONTEXT_H

#include <DartsStatistics/Contracts/Routines/iresetmodels.h>

struct PlayerStats;
template<typename T> class IStatsDb;
struct SnapShot;
class ServicesContext;

class ResetStatsContext : public IResetModels
{
public:
        typedef IStatsDb<PlayerStats> StatsDb;
    typedef IStatsDb<SnapShot> IptDb;
    ResetStatsContext(ServicesContext *provider);
    virtual void reset() override;
private:
    void resetCurrentStats();
    StatsDb *_statsDb;
    IptDb *_inputDb;
};

#endif // RESETSTATSCONTEXT_H
