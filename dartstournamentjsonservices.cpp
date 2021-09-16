#include "dartstournamentjsonservices.h"

IDartsTournamentExtractor *DartsTournamentJsonServices::tournamentExtractor() const
{
    return _tournamentExtractor;
}

void DartsTournamentJsonServices::setTournamentExtractor(IDartsTournamentExtractor *newTournamentExtractor)
{
    _tournamentExtractor = newTournamentExtractor;
}

IAddDetailsToTournamentJson *DartsTournamentJsonServices::dartsTournamentJsonAddDetails() const
{
    return _dartsTournamentJsonAddDetails;
}

void DartsTournamentJsonServices::setDartsTournamentJsonAddDetails(IAddDetailsToTournamentJson *newDartsTournamentJsonAddDetails)
{
    _dartsTournamentJsonAddDetails = newDartsTournamentJsonAddDetails;
}

IDartsTournamentJsonBuilder *DartsTournamentJsonServices::dartsTournamentCreateJson() const
{
    return _dartsTournamentCreateJson;
}

void DartsTournamentJsonServices::setDartsTournamentCreateJson(IDartsTournamentJsonBuilder *newDartsTournamentCreateJson)
{
    _dartsTournamentCreateJson = newDartsTournamentCreateJson;
}

ICreateTournamentWinnerJson *DartsTournamentJsonServices::createTournamentWinnerJson() const
{
    return _createTournamentWinnerJson;
}

void DartsTournamentJsonServices::setCreateTournamentWinnerJson(ICreateTournamentWinnerJson *newCreateTournamentWinnerJson)
{
    _createTournamentWinnerJson = newCreateTournamentWinnerJson;
}

IExtractWinnerInfo *DartsTournamentJsonServices::extractWinnerInfoFromJson() const
{
    return _extractWinnerInfo;
}

void DartsTournamentJsonServices::setExtractWinnerInfoService(IExtractWinnerInfo *newGetDartsTournamentDataFromJson)
{
    _extractWinnerInfo = newGetDartsTournamentDataFromJson;
}

ICreateJsonFromTournamentDetails *DartsTournamentJsonServices::createJsonFromDetails() const
{
    return _createJsonFromDetails;
}

void DartsTournamentJsonServices::setCreateJsonFromDetails(ICreateJsonFromTournamentDetails *newCreateJsonFromDetails)
{
    _createJsonFromDetails = newCreateJsonFromDetails;
}

IDartsCreateJsonMetaData *DartsTournamentJsonServices::createJsonMetaData() const
{
    return _createJsonMetaData;
}

void DartsTournamentJsonServices::setCreateJsonMetaData(IDartsCreateJsonMetaData *newCreateJsonMetaData)
{
    _createJsonMetaData = newCreateJsonMetaData;
}

IJsonToDartsTournamentModel *DartsTournamentJsonServices::createDartsTournament() const
{
    return _createDartsTournament;
}

void DartsTournamentJsonServices::setCreateDartsTournament(IJsonToDartsTournamentModel *newCreateDartsTournament)
{
    _createDartsTournament = newCreateDartsTournament;
}
