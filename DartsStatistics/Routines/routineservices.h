#ifndef ROUTINESERVICES_H
#define ROUTINESERVICES_H

#include "IUpdateCurrentStats.h"
#include "iresetmodels.h"
#include <DartsStatistics/InputRoutines/IRemoveInputFromDb.h>
#include <DartsStatistics/Report/icreatereport.h>

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
