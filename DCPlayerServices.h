#ifndef DCPLAYERSERVICES_H
#define DCPLAYERSERVICES_H

#include <idcgetplayername.h>
#include <idcgetwinnermodelfromjson.h>
#include <idcplayerservice.h>
#include "idccreateplayersfromjson.h"

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

    IJsonKeysPlayer *winnerKeys() const
    {
        return _winnerKeys;
    }
    void setWinnerKeys(IJsonKeysPlayer *newWinnerKeys)
    {
        _winnerKeys = newWinnerKeys;
    }

    IJsonKeysPlayer *playerKeys() const
    {
        return _defaultPlayerKeys;
    }
    void setPlayerKeys(IJsonKeysPlayer *newDefaultPlayerKeys)
    {
        _defaultPlayerKeys = newDefaultPlayerKeys;
    }
private:
    IDCGetWinnerModelFromJson *_winnerModelFromJson;
    IDCPlayerService *_playerService;
    IDCGetPlayerName *_getPlayerName;
    IDCCreatePlayersFromJson *_createPlayersFromJson;
    IJsonKeysPlayer *_winnerKeys;
    IJsonKeysPlayer *_defaultPlayerKeys;
};
#endif // DCPLAYERSERVICES_H
