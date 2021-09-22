#include "dartstournamentmodelsservices.h"

IAddPlayerDetailsToTournament *DartsTournamentModelsServices::addToTournamentModel() const
{
    return _addPlayerDetails;
}

void DartsTournamentModelsServices::setAddToTournamentModel(IAddPlayerDetailsToTournament *newDartsModelManipulator)
{
    _addPlayerDetails = newDartsModelManipulator;
}

IGetDartsTournamentFromDb *DartsTournamentModelsServices::getTournament() const
{
    return _getTournament;
}

void DartsTournamentModelsServices::setGetTournament(IGetDartsTournamentFromDb *newGetTournament)
{
    _getTournament = newGetTournament;
}

IModelsDbContext *DartsTournamentModelsServices::dartsTournamentDb() const
{
    return _dartsTournamentsDb;
}

void DartsTournamentModelsServices::setDartsTournamentDb(IModelsDbContext *newDartsTournamentDb)
{
    _dartsTournamentsDb = newDartsTournamentDb;
}

IGetTournamentWinner *DartsTournamentModelsServices::getTournamenWinnerModel() const
{
    return _getTournamenWinnerModel;
}

void DartsTournamentModelsServices::setGetTournamenWinnerModel(IGetTournamentWinner *newGetTournamenWinnerModel)
{
    _getTournamenWinnerModel = newGetTournamenWinnerModel;
}








