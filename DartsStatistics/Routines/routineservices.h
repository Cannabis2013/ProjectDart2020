#ifndef ROUTINESERVICES_H
#define ROUTINESERVICES_H
#include "Routines/IJsonToModels.h"
#include "Players/Models/imirrorsdb.h"
#include "Routines/iaddplayerstomem.h"
#include "Inputs/Models/snapshot.h"
#include "Routines/iresetmodels.h"
#include "IAddStatsToPlayer.h"
#include "InputRoutines/IRemoveInputFromDb.h"
#include "Report/icreatereport.h"
class RoutineServices
{
public:
    typedef IJsonToModels<CurrentStat> JsonToStats;
    typedef IJsonToModels<SnapShot> JsonToInputs;
    typedef IAddStatsToPlayer<SnapShot> UpdateCurrentStats;
    JsonToStats *byteArrayToStats() const {return _convertToPlayers;}
    void setConvertToPlayers(JsonToStats *service) {_convertToPlayers = service;}
    JsonToInputs *byteArrayToSnapShots() const {return _convertToInputs;}
    void setConvertToInputs(JsonToInputs *service) {_convertToInputs = service;}
    IResetModels *resetContext() const {return _resetPlayers;}
    void setResetContext(IResetModels *service) {_resetPlayers = service;}
    UpdateCurrentStats *updatePlayerStatistics() const {return _updateStats;}
    void setUpdateStats(UpdateCurrentStats *service) {_updateStats = service;}
    IRemoveInputFromDb *removeSnapShot() const {return _removeInputFromDb;}
    void setRemoveInputFromDb(IRemoveInputFromDb *service) {_removeInputFromDb = service;}
    ICreateReport *createReport() const {return _createReport;}
    void setCreateReport(ICreateReport *service) {_createReport = service;}
private:
    JsonToStats *_convertToPlayers;
    JsonToInputs *_convertToInputs;
    IResetModels *_resetPlayers;
    UpdateCurrentStats *_updateStats;
    IRemoveInputFromDb *_removeInputFromDb;
    ICreateReport *_createReport;
};
#endif // ROUTINESERVICES_H
