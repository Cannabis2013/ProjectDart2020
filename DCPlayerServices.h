#ifndef DCPLAYERSERVICES_H
#define DCPLAYERSERVICES_H

#include <idcgetplayername.h>
#include <idcplayerservice.h>

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
private:
    IDCPlayerService *_playerService;
    IDCGetPlayerName *_getPlayerName;
};
#endif // DCPLAYERSERVICES_H
