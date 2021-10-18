#ifndef DCPLAYERSLAS_H
#define DCPLAYERSLAS_H

#include "DartsController/DCPlayerSLAs/idcgetwinnermodelfromjson.h"
#include "DartsController/DCPlayerSLAs/idcplayerservice.h"
#include "IDCPlayerApproval.h"

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
    IDCPlayerBuilder *playerBuilder() const
    {
        return _playerBuilderService;
    }
    void setPlayerBuilderService(IDCPlayerBuilder *service)
    {
        _playerBuilderService = service;
    }
    IDCPlayerApproval *playerAllowanceContext() const
    {
        return _playerAllowanceContext;
    }
    void setPlayerAllowanceContext(IDCPlayerApproval *newPlayerAllowanceContext)
    {
        _playerAllowanceContext = newPlayerAllowanceContext;
    }
private:
    IDCGetWinnerModelFromJson *_winnerModelFromJson;
    IDCPlayerService *_playerService;
    IDCPlayerKeys *_winnerKeys;
    IDCPlayerKeys *_defaultPlayerKeys;
    IDCPlayerBuilder* _playerBuilderService;
    IDCPlayerApproval *_playerAllowanceContext = nullptr;
};
#endif // DCPLAYERSLAS_H
