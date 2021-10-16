#ifndef DARTSTOURNAMENTSLAS_H
#define DARTSTOURNAMENTSLAS_H
#include "DartsModelsContext/TournamentsSLAs/isettournamentplayerdetails.h"
#include "DartsModelsContext/TournamentsSLAs/iwinnerinfobuilder.h"
#include "idartsmetamodelbuilder.h"
#include "igettournamentids.h"
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
    IDartsMetaModelBuilder *metaModelBuilder() const
    {
        return _metaModelBuilder;
    }
    void setMetaModelBuilder(IDartsMetaModelBuilder *newMetaModelBuilder)
    {
        _metaModelBuilder = newMetaModelBuilder;
    }
private:
    IDartsMetaModelBuilder *_metaModelBuilder;
    IGetDartsTournamentIds *_getTournamentIds;
    ISetTournamentPlayerDetails *_addPlayerDetails;
    IWinnerInfoBuilder *_winnerInfoBuilder;
};
#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
