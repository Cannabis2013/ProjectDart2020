#ifndef RESETSTATSCONTEXT_H
#define RESETSTATSCONTEXT_H
#include "Routines/iresetmodels.h"
template<typename T> class IStatsDb;
struct Input;
struct CurrentStats;
class ServicesContext;
class ResetStatsContext : public IResetModels
{
public:
    typedef IStatsDb<CurrentStats> StatsDb;
    typedef IStatsDb<Input> IptDb;
    ResetStatsContext(ServicesContext *provider);
    virtual void reset() override;
private:
    void resetCurrentStats();
    StatsDb *_statsDb;
    IptDb *_iptDb;
};

#endif // RESETSTATSCONTEXT_H
