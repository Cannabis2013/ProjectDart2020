#ifndef ROUTINESERVICES_H
#define ROUTINESERVICES_H
#include "Routines/IJsonToModels.h"
#include "Models/playerstat.h"
#include "Routines/iaddplayerstomem.h"
#include "Inputs/input.h"
#include "Routines/iresetmodels.h"
class StatsRoutineServices
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
private:
    JsonToPlayers *_convertToPlayers;
    AddPlayersToMemory *_addPlayersToMemory;
    JsonToInputs *_convertToInputs;
    AddInputsToMemory *_addInputsToMemory;
    IResetModels *_resetPlayers;
    IResetModels *_resetInputs;
};
#endif // ROUTINESERVICES_H
