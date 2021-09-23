#ifndef DCPLAYERSERVICES_H
#define DCPLAYERSERVICES_H

#include "DartsController/DCPlayerSLAs/idcgetplayername.h"
#include "DartsController/DCPlayerSLAs/idcgetwinnermodelfromjson.h"
#include "DartsController/DCPlayerSLAs/idcplayerservice.h"
#include "DartsController/DCPlayerSLAs/icreatejsonfromdcplayer.h"
#include "DartsController/DCPlayerSLAs/idccreateplayersfromjson.h"

class DCPlayerServices
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
    IDCGetPlayerName *getPlayerName() const
    {
        return _getPlayerName;
    }
    void setGetPlayerName(IDCGetPlayerName *newGetPlayerName)
    {
        _getPlayerName = newGetPlayerName;
    }
    IDCGetWinnerModelFromJson *winnerModelFromJson() const
    {
        return _winnerModelFromJson;
    }
    void setWinnerModelFromJson(IDCGetWinnerModelFromJson *newWinnerModelFromJson)
    {
        _winnerModelFromJson = newWinnerModelFromJson;
    }
    IDCCreatePlayersFromJson *createPlayersFromJson() const
    {
        return _createPlayersFromJson;
    }
    void setCreatePlayersFromJson(IDCCreatePlayersFromJson *newCreatePlayersFromJson)
    {
        _createPlayersFromJson = newCreatePlayersFromJson;
    }

    IDCPlayerKeys *winnerKeys() const
    {
        return _winnerKeys;
    }
    void setWinnerKeys(IDCPlayerKeys *newWinnerKeys)
    {
        _winnerKeys = newWinnerKeys;
    }

    IDCPlayerKeys *playerKeys() const
    {
        return _defaultPlayerKeys;
    }
    void setPlayerKeys(IDCPlayerKeys *newDefaultPlayerKeys)
    {
        _defaultPlayerKeys = newDefaultPlayerKeys;
    }
    IDCPlayerModelBuilder *playerBuilder() const
    {
        return _playerBuilderService;
    }
    void setPlayerBuilderService(IDCPlayerModelBuilder *newPlayerBuilderService)
    {
        _playerBuilderService = newPlayerBuilderService;
    }
    ICreateJsonFromDCPlayer *createJsonFromPlayer() const
    {
        return _createJsonFromPlayer;
    }
    void setCreateJsonFromPlayer(ICreateJsonFromDCPlayer *newCreateJsonFromPlayer)
    {
        _createJsonFromPlayer = newCreateJsonFromPlayer;
    }
private:
    IDCGetWinnerModelFromJson *_winnerModelFromJson;
    IDCPlayerService *_playerService;
    IDCGetPlayerName *_getPlayerName;
    IDCCreatePlayersFromJson *_createPlayersFromJson;
    IDCPlayerKeys *_winnerKeys;
    IDCPlayerKeys *_defaultPlayerKeys;
    IDCPlayerModelBuilder* _playerBuilderService;
    ICreateJsonFromDCPlayer *_createJsonFromPlayer;
};
#endif // DCPLAYERSERVICES_H
