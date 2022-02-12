#ifndef ROUTINESERVICES_H
#define ROUTINESERVICES_H
#include "Players/Models/currentstats.h"
#include "Routines/iaddplayerstomem.h"
#include "Inputs/Models/snapshot.h"
#include "Routines/iresetmodels.h"
#include "IUpdateCurrentStats.h"
#include "InputRoutines/IRemoveInputFromDb.h"
#include "Report/icreatereport.h"
class RoutineServices
{
public:
    typedef IUpdateCurrentStats<SnapShot> UpdateCurrentStats;
    IResetModels *resetContext() const {return _resetPlayers;}
    void setResetContext(IResetModels *service) {_resetPlayers = service;}
    UpdateCurrentStats *updatePlayerStatistics() const {return _updateStats;}
    void setUpdateStats(UpdateCurrentStats *service) {_updateStats = service;}
    IRemoveInputFromDb *removeSnapShot() const {return _removeInputFromDb;}
    void setRemoveInputFromDb(IRemoveInputFromDb *service) {_removeInputFromDb = service;}
    ICreateReport *createReport() const {return _createReport;}
    void setCreateReport(ICreateReport *service) {_createReport = service;}
private:
    IResetModels *_resetPlayers;
    UpdateCurrentStats *_updateStats;
    IRemoveInputFromDb *_removeInputFromDb;
    ICreateReport *_createReport;
};
#endif // ROUTINESERVICES_H
