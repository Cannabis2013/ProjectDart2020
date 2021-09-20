#ifndef DCMETASERVICES_H
#define DCMETASERVICES_H
#include "idcmetastatus.h"
#include "idartsstatuscodes.h"
#include "idchint.h"
#include "idctournamentid.h"
class DCMetaServices
{
public:
    IDCMetaStatus *metaStatus() const
    {
        return _metaStatus;
    }
    void setMetaStatus(IDCMetaStatus *newMetaStatus)
    {
        _metaStatus = newMetaStatus;
    }
    IDartsStatusCodes *statusCodes() const
    {
        return _statusCodes;
    }
    void setStatusCodes(IDartsStatusCodes *newStatusCodes)
    {
        _statusCodes = newStatusCodes;
    }
    IDCHint *inputHint() const
    {
        return _inputHint;
    }
    void setInputHint(IDCHint *newInputHint)
    {
        _inputHint = newInputHint;
    }

    IDCHint *displayHint() const
    {
        return _displayHint;
    }
    void setDisplayHint(IDCHint *newDisplayHint)
    {
        _displayHint = newDisplayHint;
    }

    IDCTournamentId *tournamentId() const
    {
        return _tournamentId;
    }
    void setTournamentId(IDCTournamentId *newTournamentId)
    {
        _tournamentId = newTournamentId;
    }
private:
    IDCMetaStatus *_metaStatus;
    IDartsStatusCodes *_statusCodes;
    IDCTournamentId *_tournamentId;
    IDCHint *_inputHint;
    IDCHint *_displayHint;
};
#endif // DCMETASERVICES_H
