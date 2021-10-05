#ifndef DCMETASERVICES_H
#define DCMETASERVICES_H
#include "DartsController/DCMetaSLAs/idcstatus.h"
#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
#include "DartsController/DCMetaSLAs/idchint.h"
#include "DartsController/DCMetaSLAs/idctournamentid.h"
#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include "DartsController/DCMetaSLAs/idcwinnerservice.h"
#include "DartsController/DCMetaSLAs/idartsdeterminestatusbyid.h"
class DCMetaServices
{
public:
    IDCStatus *controllerStatus() const
    {
        return _controllerStatus;
    }
    void setControllerStatus(IDCStatus *service)
    {
        _controllerStatus = service;
    }
    IDartsStatusCodes *statusCodes() const
    {
        return _statusCodes;
    }
    void setStatusCodes(IDartsStatusCodes *service)
    {
        _statusCodes = service;
    }
    IDCHint *inputHint() const
    {
        return _inputHint;
    }
    void setInputHint(IDCHint *service)
    {
        _inputHint = service;
    }

    IDCHint *displayHint() const
    {
        return _displayHint;
    }
    void setDisplayHint(IDCHint *service)
    {
        _displayHint = service;
    }

    IDCTournamentId *tournamentId() const
    {
        return _tournamentId;
    }
    void setTournamentId(IDCTournamentId *service)
    {
        _tournamentId = service;
    }
    IDCInitialScore *initialScore() const
    {
        return _initialScore;
    }
    void setInitialScore(IDCInitialScore *service)
    {
        _initialScore = service;
    }
    IDCWinnerService *winnerService() const
    {
        return _winnerService;
    }
    void setWinnerService(IDCWinnerService *service)
    {
        _winnerService = service;
    }
    IDartsDetermineStatusById *determineStatusById() const
    {
        return _determineStatusById;
    }
    void setDetermineStatusById(IDartsDetermineStatusById *newDetermineStatusById)
    {
        _determineStatusById = newDetermineStatusById;
    }
private:
    IDCStatus *_controllerStatus;
    IDartsStatusCodes *_statusCodes;
    IDCTournamentId *_tournamentId;
    IDCHint *_inputHint;
    IDCHint *_displayHint;
    IDCInitialScore *_initialScore;
    IDCWinnerService *_winnerService = nullptr;
    IDartsDetermineStatusById* _determineStatusById;
};
#endif // DCMETASERVICES_H
