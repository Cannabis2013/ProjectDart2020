#include "dartstournamentslas.h"
IAddPlayerDetailsToTournament *DartsTournamentSLAs::addToTournamentModel() const
{
    return _addPlayerDetails;
}
void DartsTournamentSLAs::setAddToTournamentModel(IAddPlayerDetailsToTournament *newDartsModelManipulator)
{
    _addPlayerDetails = newDartsModelManipulator;
}
IGetDartsTournamentFromDb *DartsTournamentSLAs::getTournament() const
{
    return _getTournament;
}
void DartsTournamentSLAs::setGetTournament(IGetDartsTournamentFromDb *newGetTournament)
{
    _getTournament = newGetTournament;
}
IModelsDbContext *DartsTournamentSLAs::dartsTournamentDb() const
{
    return _dartsTournamentsDb;
}
void DartsTournamentSLAs::setDartsTournamentDb(IModelsDbContext *newDartsTournamentDb)
{
    _dartsTournamentsDb = newDartsTournamentDb;
}
IGetTournamentWinner *DartsTournamentSLAs::getTournamenWinnerModel() const
{
    return _getTournamenWinnerModel;
}
void DartsTournamentSLAs::setGetTournamenWinnerModel(IGetTournamentWinner *newGetTournamenWinnerModel)
{
    _getTournamenWinnerModel = newGetTournamenWinnerModel;
}
IDartsTournamentExtractor *DartsTournamentSLAs::tournamentExtractor() const
{
    return _tournamentExtractor;
}
void DartsTournamentSLAs::setTournamentExtractor(IDartsTournamentExtractor *newTournamentExtractor)
{
    _tournamentExtractor = newTournamentExtractor;
}
IAddDetailsToTournamentJson *DartsTournamentSLAs::dartsTournamentJsonAddDetails() const
{
    return _dartsTournamentJsonAddDetails;
}

void DartsTournamentSLAs::setDartsTournamentJsonAddDetails(IAddDetailsToTournamentJson *newDartsTournamentJsonAddDetails)
{
    _dartsTournamentJsonAddDetails = newDartsTournamentJsonAddDetails;
}

IDartsTournamentJsonBuilder *DartsTournamentSLAs::dartsTournamentCreateJson() const
{
    return _dartsTournamentCreateJson;
}

void DartsTournamentSLAs::setDartsTournamentCreateJson(IDartsTournamentJsonBuilder *newDartsTournamentCreateJson)
{
    _dartsTournamentCreateJson = newDartsTournamentCreateJson;
}
IExtractWinnerInfo *DartsTournamentSLAs::extractWinnerInfoFromJson() const
{
    return _extractWinnerInfo;
}
void DartsTournamentSLAs::setExtractWinnerInfoService(IExtractWinnerInfo *newGetDartsTournamentDataFromJson)
{
    _extractWinnerInfo = newGetDartsTournamentDataFromJson;
}
ICreateJsonFromTournamentDetails *DartsTournamentSLAs::createJsonFromDetails() const
{
    return _createJsonFromDetails;
}
void DartsTournamentSLAs::setCreateJsonFromDetails(ICreateJsonFromTournamentDetails *newCreateJsonFromDetails)
{
    _createJsonFromDetails = newCreateJsonFromDetails;
}
IDartsCreateJsonMetaData *DartsTournamentSLAs::createJsonMetaData() const
{
    return _createJsonMetaData;
}
void DartsTournamentSLAs::setCreateJsonMetaData(IDartsCreateJsonMetaData *newCreateJsonMetaData)
{
    _createJsonMetaData = newCreateJsonMetaData;
}
IJsonToDartsTournamentModel *DartsTournamentSLAs::createDartsTournament() const
{
    return _createDartsTournament;
}
void DartsTournamentSLAs::setCreateDartsTournament(IJsonToDartsTournamentModel *newCreateDartsTournament)
{
    _createDartsTournament = newCreateDartsTournament;
}
