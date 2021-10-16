#ifndef DCPLAYERSLAS_H
#define DCPLAYERSLAS_H

#include "DartsController/DCPlayerSLAs/idcgetwinnermodelfromjson.h"
#include "DartsController/DCPlayerSLAs/idcplayerservice.h"
#include "DartsController/DCPlayerSLAs/idcplayerjsonbuilder.h"
#include "DartsController/DCPlayerSLAs/idccreateplayersfromjson.h"
#include "IDCPlayerAllowancesContext.h"

class DCPlayerSLAs
{
public:
    IDCPlayerService *playerService() const
    {
        return _playerService;
    }
    void setPlayerService(IDCPlayerService *service)
    {
        _playerService = service;
    }
    IDCGetWinnerModelFromJson *winnerModelFromJson() const
    {
        return _winnerModelFromJson;
    }
    void setWinnerModelFromJson(IDCGetWinnerModelFromJson *service)
    {
        _winnerModelFromJson = service;
    }
    IDCCreatePlayersFromJson *createPlayersFromJson() const
    {
        return _createPlayersFromJson;
    }
    void setCreatePlayersFromJson(IDCCreatePlayersFromJson *service)
    {
        _createPlayersFromJson = service;
    }

    IDCPlayerKeys *winnerKeys() const
    {
        return _winnerKeys;
    }
    void setWinnerKeys(IDCPlayerKeys *service)
    {
        _winnerKeys = service;
    }

    IDCPlayerKeys *playerKeys() const
    {
        return _defaultPlayerKeys;
    }
    void setPlayerKeys(IDCPlayerKeys *service)
    {
        _defaultPlayerKeys = service;
    }
    IDCPlayerModelBuilder *playerBuilder() const
    {
        return _playerBuilderService;
    }
    void setPlayerBuilderService(IDCPlayerModelBuilder *service)
    {
        _playerBuilderService = service;
    }
    IDCPlayerJsonBuilder *createJsonFromPlayer() const
    {
        return _createJsonFromPlayer;
    }
    void setCreateJsonFromPlayer(IDCPlayerJsonBuilder *service)
    {
        _createJsonFromPlayer = service;
    }
    IDCPlayerAllowancesContext *playerAllowanceContext() const
    {
        return _playerAllowanceContext;
    }
    void setPlayerAllowanceContext(IDCPlayerAllowancesContext *newPlayerAllowanceContext)
    {
        _playerAllowanceContext = newPlayerAllowanceContext;
    }
private:
    IDCGetWinnerModelFromJson *_winnerModelFromJson;
    IDCPlayerService *_playerService;
    IDCCreatePlayersFromJson *_createPlayersFromJson;
    IDCPlayerKeys *_winnerKeys;
    IDCPlayerKeys *_defaultPlayerKeys;
    IDCPlayerModelBuilder* _playerBuilderService;
    IDCPlayerJsonBuilder *_createJsonFromPlayer;
    IDCPlayerAllowancesContext *_playerAllowanceContext = nullptr;
};




#endif // DCPLAYERSLAS_H
