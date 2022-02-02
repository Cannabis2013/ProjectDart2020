#ifndef ROUTINESERVICES_H
#define ROUTINESERVICES_H
#include "Routines/IJsonToModels.h"
#include "Players/Models/playerstat.h"
#include "Routines/iaddplayerstomem.h"
#include "Inputs/Models/input.h"
#include "Routines/iresetmodels.h"
#include "IAddStatsToPlayer.h"
#include "igetplayer.h"
class RoutineServices
{
public:
    typedef PlayerStat Player;
    typedef IJsonToModels<Player> JsonToPlayers;
    typedef IJsonToModels<Input> JsonToInputs;
    typedef IAddModelsToMemory<Player> AddPlayersToMemory;
    typedef IAddModelsToMemory<Input> AddInputsToMemory;
    JsonToPlayers *convertToPlayers() const {return _convertToPlayers;}
    void setConvertToPlayers(JsonToPlayers *service) {_convertToPlayers = service;}
    AddPlayersToMemory *addPlayersToMemory() const {return _addPlayersToMemory;}
    void setAddPlayersToMemory(AddPlayersToMemory *service) {_addPlayersToMemory = service;}
    AddInputsToMemory *addInputsToMemory() const {return _addInputsToMemory;}
    void setAddInputsToMemory(AddInputsToMemory *service) {_addInputsToMemory = service;}
    JsonToInputs *convertToInputs() const {return _convertToInputs;}
    void setConvertToInputs(JsonToInputs *service) {_convertToInputs = service;}
    IResetModels *resetPlayers() const {return _resetPlayers;}
    void setResetPlayers(IResetModels *service) {_resetPlayers = service;}
    IResetModels *resetInputs() const {return _resetInputs;}
    void setResetInputs(IResetModels *service) {_resetInputs = service;}
    IAddStatsToPlayer *updatePlayerStatistics() const {return _updateStats;}
    void setUpdateStats(IAddStatsToPlayer *newUpdateStats) {_updateStats = newUpdateStats;}
    IGetPlayer *getPlayer() const {return _getPlayer;}
    void setGetPlayer(IGetPlayer *newGetPlayer) {_getPlayer = newGetPlayer;}
private:
    JsonToPlayers *_convertToPlayers;
    AddPlayersToMemory *_addPlayersToMemory;
    JsonToInputs *_convertToInputs;
    AddInputsToMemory *_addInputsToMemory;
    IResetModels *_resetPlayers;
    IResetModels *_resetInputs;
    IAddStatsToPlayer *_updateStats;
    IGetPlayer *_getPlayer;
};
#endif // ROUTINESERVICES_H
