#include "dartstournamentservices.h"

IAddPlayerDetailsToTournament *DartsTournamentServices::addToTournamentModel() const
{
    return _addPlayerDetails;
}

void DartsTournamentServices::setAddToTournamentModel(IAddPlayerDetailsToTournament *newDartsModelManipulator)
{
    _addPlayerDetails = newDartsModelManipulator;
}

IDartsTournamentJsonBuilder *DartsTournamentServices::createJsonFromDartsTournamentModels() const
{
    return _dartsTournamentCreateJson;
}

void DartsTournamentServices::setCreateJsonFromDartsTournamentModels(IDartsTournamentJsonBuilder *service)
{
    _dartsTournamentCreateJson = service;
}

IGetDartsTournamentFromDb *DartsTournamentServices::getTournament() const
{
    return _getTournament;
}

void DartsTournamentServices::setGetTournament(IGetDartsTournamentFromDb *newGetTournament)
{
    _getTournament = newGetTournament;
}

IDartsTournamentNumberOfAttempts *DartsTournamentServices::getNumberOfAttempts() const
{
    return _getNumberOfAttempts;
}

void DartsTournamentServices::setGetNumberOfAttempts(IDartsTournamentNumberOfAttempts *newGetNumberOfAttempts)
{
    _getNumberOfAttempts = newGetNumberOfAttempts;
}

IModelsDbContext *DartsTournamentServices::dartsTournamentDb() const
{
    return _dartsTournamentsDb;
}

void DartsTournamentServices::setDartsTournamentDb(IModelsDbContext *newDartsTournamentDb)
{
    _dartsTournamentsDb = newDartsTournamentDb;
}

IDartsTournamentJsonBuilder *DartsTournamentServices::dartsTournamentCreateJson() const
{
    return _dartsTournamentCreateJson;
}

void DartsTournamentServices::setDartsTournamentCreateJson(IDartsTournamentJsonBuilder *newDartsTournamentCreateJson)
{
    _dartsTournamentCreateJson = newDartsTournamentCreateJson;
}

IAddDetailsToTournamentJson *DartsTournamentServices::dartsTournamentJsonAddDetails() const
{
    return _dartsTournamentJsonAddDetails;
}

void DartsTournamentServices::setDartsTournamentJsonAddDetails(IAddDetailsToTournamentJson *newDartsTournamentJsonAddDetails)
{
    _dartsTournamentJsonAddDetails = newDartsTournamentJsonAddDetails;
}

DartsTournamentServices::TournamentBuilder *DartsTournamentServices::createDartsTournament() const
{
    return _createDartsTournament;
}

void DartsTournamentServices::setCreateDartsTournament(TournamentBuilder *newCreateDartsTournament)
{
    _createDartsTournament = newCreateDartsTournament;
}

IExtractWinnerInfo *DartsTournamentServices::extractWinnerInfoFromJson() const
{
    return _getDartsTournamentDataFromJson;
}

void DartsTournamentServices::setGetDartsTournamentDataFromJson(IExtractWinnerInfo *newGetDartsTournamentDataFromJson)
{
    _getDartsTournamentDataFromJson = newGetDartsTournamentDataFromJson;
}

IDartsCreateJsonMetaData *DartsTournamentServices::createJsonMetaData() const
{
    return _createJsonMetaData;
}

void DartsTournamentServices::setCreateJsonMetaData(IDartsCreateJsonMetaData *newCreateJsonMetaData)
{
    _createJsonMetaData = newCreateJsonMetaData;
}

IGetTournamentWinner *DartsTournamentServices::getTournamenWinnerModel() const
{
    return _getTournamenWinnerModel;
}

void DartsTournamentServices::setGetTournamenWinnerModel(IGetTournamentWinner *newGetTournamenWinnerModel)
{
    _getTournamenWinnerModel = newGetTournamenWinnerModel;
}

ICreateTournamentWinnerJson *DartsTournamentServices::createTournamentWinnerJson() const
{
    return _createTournamentWinnerJson;
}

void DartsTournamentServices::setCreateTournamentWinnerJson(ICreateTournamentWinnerJson *newCreateTournamentWinnerJson)
{
    _createTournamentWinnerJson = newCreateTournamentWinnerJson;
}

ICreateJsonFromTournamentDetails *DartsTournamentServices::createJsonFromDetails() const
{
    return _createJsonFromDetails;
}

void DartsTournamentServices::setCreateJsonFromDetails(ICreateJsonFromTournamentDetails *newCreateJsonFromDetails)
{
    _createJsonFromDetails = newCreateJsonFromDetails;
}
