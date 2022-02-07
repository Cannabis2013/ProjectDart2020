#ifndef SERVICESCONTEXT_H
#define SERVICESCONTEXT_H
#include "Players/currentstatsservices.h"
#include "Inputs/inputservices.h"
#include "StatsServices/StatsServices.h"
#include "Routines/routineservices.h"
class ServicesContext
{
public:
    CurrentStatsServices *currentStatsServices() const {return _playerServices;}
    void setPlayerServices(CurrentStatsServices *service) {_playerServices = service;}
    InputServices *inputServices() const {return _inputServices;}
    void setInputServices(InputServices *service) {_inputServices = service;}
    StatsServices *statsServices() const {return _statsServices;}
    void setStatsProvider(StatsServices *services) {_statsServices = services;}
    RoutineServices *routines() const {return _routines;}
    void setRoutines(RoutineServices *service) {_routines = service;}
private:
    CurrentStatsServices *_playerServices;
    InputServices *_inputServices;
    StatsServices *_statsServices;
    RoutineServices *_routines;
};
#endif // STATISTICSSERVICES_H
