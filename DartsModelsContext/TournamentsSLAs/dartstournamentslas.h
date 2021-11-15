#ifndef DARTSTOURNAMENTSLAS_H
#define DARTSTOURNAMENTSLAS_H
#include "DartsModelsContext/TournamentsSLAs/isettournamentplayerdetails.h"
#include "DartsModelsContext/TournamentsSLAs/iwinnerinfobuilder.h"
#include "idartsconsistency.h"
#include "idartsmetamodelbuilder.h"
#include "idartsrepair.h"
#include "igettournamentids.h"
#include "iresetdartstournament.h"
class DartsTournamentSLAs
{
public:
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
    IGetDartsTournamentIds *getTournamentIds() const
    {
        return _getTournamentIds;
    }
    void setGetTournamentIds(IGetDartsTournamentIds *newGetTournamentIds)
    {
        _getTournamentIds = newGetTournamentIds;
    }
    IDartsMetaModelBuilder *dartsMetaBuilder() const
    {
        return _metaModelBuilder;
    }
    void setMetaModelBuilder(IDartsMetaModelBuilder *newMetaModelBuilder)
    {
        _metaModelBuilder = newMetaModelBuilder;
    }
    IResetDartsTournament *resetDarts() const
    {
        return _resetTournament;
    }
    void setResetTournament(IResetDartsTournament *newResetTournament)
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

    IDartsRepair *tournamentRepair() const
    {
        return _tournamentRepair;
    }
    void setTournamentRepair(IDartsRepair *newTournamentRepair)
    {
        _tournamentRepair = newTournamentRepair;
    }
private:
    IResetDartsTournament *_resetTournament;
    IDartsMetaModelBuilder *_metaModelBuilder;
    IGetDartsTournamentIds *_getTournamentIds;
    ISetTournamentPlayerDetails *_addPlayerDetails;
    IWinnerInfoBuilder *_winnerInfoBuilder;
    IDartsConsistency *_verifyConsistency;
    IDartsRepair *_tournamentRepair;
};
#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
