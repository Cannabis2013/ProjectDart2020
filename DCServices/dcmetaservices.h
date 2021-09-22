#ifndef DCMETASERVICES_H
#define DCMETASERVICES_H
#include "idcmetastatus.h"
#include "idartsstatuscodes.h"
#include "idchint.h"
#include "idctournamentid.h"
#include "idcinitialscore.h"
#include "idcwinnerservice.h"
class DCMetaServices
{
public:
    IDCMetaStatus *metaStatus() const
    {
        return _metaStatus;
    }
    void setMetaStatus(IDCMetaStatus *service)
    {
        _metaStatus = service;
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
private:
    IDCMetaStatus *_metaStatus;
    IDartsStatusCodes *_statusCodes;
    IDCTournamentId *_tournamentId;
    IDCHint *_inputHint;
    IDCHint *_displayHint;
    IDCInitialScore *_initialScore;
    IDCWinnerService *_winnerService = nullptr;
};
#endif // DCMETASERVICES_H
