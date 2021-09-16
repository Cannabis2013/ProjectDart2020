#include "dartsmodelsservices.h"

IAddPlayerDetailsToTournament *DartsModelsServices::addToTournamentModel() const
{
    return _addPlayerDetails;
}

void DartsModelsServices::setAddToTournamentModel(IAddPlayerDetailsToTournament *newDartsModelManipulator)
{
    _addPlayerDetails = newDartsModelManipulator;
}

IGetDartsTournamentFromDb *DartsModelsServices::getTournament() const
{
    return _getTournament;
}

void DartsModelsServices::setGetTournament(IGetDartsTournamentFromDb *newGetTournament)
{
    _getTournament = newGetTournament;
}

IDartsTournamentNumberOfAttempts *DartsModelsServices::getNumberOfAttempts() const
{
    return _getNumberOfAttempts;
}

void DartsModelsServices::setGetNumberOfAttempts(IDartsTournamentNumberOfAttempts *newGetNumberOfAttempts)
{
    _getNumberOfAttempts = newGetNumberOfAttempts;
}

IModelsDbContext *DartsModelsServices::dartsTournamentDb() const
{
    return _dartsTournamentsDb;
}

void DartsModelsServices::setDartsTournamentDb(IModelsDbContext *newDartsTournamentDb)
{
    _dartsTournamentsDb = newDartsTournamentDb;
}

IGetTournamentWinner *DartsModelsServices::getTournamenWinnerModel() const
{
    return _getTournamenWinnerModel;
}

void DartsModelsServices::setGetTournamenWinnerModel(IGetTournamentWinner *newGetTournamenWinnerModel)
{
    _getTournamenWinnerModel = newGetTournamenWinnerModel;
}








