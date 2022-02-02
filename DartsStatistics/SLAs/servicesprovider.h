#ifndef SERVICESPROVIDER_H
#define SERVICESPROVIDER_H
#include "Players/playerservices.h"
#include "Inputs/inputservices.h"
#include "StatsServices/StatsServices.h"
#include "Report/reportservices.h"
class ServicesProvider
{
public:
    PlayerServices *playerServices() const {return _playerServices;}
    void setPlayerServices(PlayerServices *service) {_playerServices = service;}
    InputServices *inputServices() const {return _inputServices;}
    void setInputServices(InputServices *service) {_inputServices = service;}
    StatsServices *statsServices() const {return _statsServices;}
    void setStatsServices(StatsServices *services) {_statsServices = services;}
    ReportServices *reportServices() const {return _reportServices;}
    void setReportServices(ReportServices *service) {_reportServices = service;}
private:
    PlayerServices *_playerServices;
    InputServices *_inputServices;
    StatsServices *_statsServices;
    ReportServices *_reportServices;
};
#endif // STATISTICSSERVICES_H
