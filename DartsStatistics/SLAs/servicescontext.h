#ifndef SERVICESCONTEXT_H
#define SERVICESCONTEXT_H

#include <DartsStatistics/Players/statisticservices.h>

#include <DartsStatistics/Inputs/snapshotsservices.h>

#include <DartsStatistics/StatsServices/StatsServices.h>

#include <DartsStatistics/Routines/routineservices.h>

class ServicesContext
{
public:
    StatisticServices *statisticServices() const {return _statisticServices;}
    void setStatisticServices(StatisticServices *service) {_statisticServices = service;}
    SnapShotsServices *snapShotServices() const {return _snapShotsServices;}
    void setSnapShotsServices(SnapShotsServices *service) {_snapShotsServices = service;}
    StatsServices *statsServices() const {return _statsServices;}
    void setStatsProvider(StatsServices *services) {_statsServices = services;}
    RoutineServices *routines() const {return _routines;}
    void setRoutines(RoutineServices *service) {_routines = service;}
private:
    StatisticServices *_statisticServices;
    SnapShotsServices *_snapShotsServices;
    StatsServices *_statsServices;
    RoutineServices *_routines;
};
#endif // STATISTICSSERVICES_H
