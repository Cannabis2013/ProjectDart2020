#ifndef DARTSSLAS_H
#define DARTSSLAS_H
#include "DartsModelsContext/TournamentsSLAs/isettournamentplayerdetails.h"
#include "DartsModelsContext/TournamentsSLAs/iwinnerinfobuilder.h"
#include "idartsconsistency.h"
#include "idartscreatemeta.h"
#include "itournamentrepair.h"
#include "igettournamentids.h"
#include "iresetdartstournament.h"
class DartsSLAs
{
public:
    typedef IModel<QUuid> BaseModel;
    ISetTournamentPlayerDetails *setTournamentPlayerDetails() const
    {
        return _addPlayerDetails;
    }
    void setSetTournamentPlayerDetails(ISetTournamentPlayerDetails *service)
    {
        _addPlayerDetails = service;
    }
    IWinnerInfoBuilder *winnerInfoBuilder() const
    {
        return _winnerInfoBuilder;
    }
    void setWinnerInfoBuilder(IWinnerInfoBuilder *service)
    {
        _winnerInfoBuilder = service;
    }
    IGetDartsTournamentIds<BaseModel> *getTournamentIds() const
    {
        return _getTournamentIds;
    }
    void setGetTournamentIds(IGetDartsTournamentIds<BaseModel> *newGetTournamentIds)
    {
        _getTournamentIds = newGetTournamentIds;
    }
    IDartsCreateMeta *createMeta() const
    {
        return _createMeta;
    }
    void setCreateMeta(IDartsCreateMeta *builder)
    {
        _createMeta = builder;
    }
    IResetDartsTournament<BaseModel> *resetDarts() const
    {
        return _resetTournament;
    }
    void setResetTournament(IResetDartsTournament<BaseModel> *newResetTournament)
    {
        _resetTournament = newResetTournament;
    }
    IDartsConsistency *verifyConsistency() const
    {
        return _verifyConsistency;
    }
    void setVerifyConsistency(IDartsConsistency *newVerifyConsistency)
    {
        _verifyConsistency = newVerifyConsistency;
    }

    ITournamentRepair *tournamentRepair() const
    {
        return _tournamentRepair;
    }
    void setTournamentRepair(ITournamentRepair *newTournamentRepair)
    {
        _tournamentRepair = newTournamentRepair;
    }
private:
    IResetDartsTournament<BaseModel> *_resetTournament;
    IDartsCreateMeta *_createMeta;
    IGetDartsTournamentIds<BaseModel> *_getTournamentIds;
    ISetTournamentPlayerDetails *_addPlayerDetails;
    IWinnerInfoBuilder *_winnerInfoBuilder;
    IDartsConsistency *_verifyConsistency;
    ITournamentRepair *_tournamentRepair;
};
#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
