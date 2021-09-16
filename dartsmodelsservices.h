#ifndef DARTSMODELSSERVICES_H
#define DARTSMODELSSERVICES_H

#include "idartscreatejsonmetadata.h"
#include "iaddplayerdetailstotournament.h"
#include "ijsontodartstournamentmodel.h"
#include "idartstournamentjsonbuilder.h"
#include "idartstournamentnumberofattempts.h"
#include "iextractwinnerinfo.h"
#include "igetdartstournamentfromdb.h"
#include "igettournamentwinner.h"
#include "icreatetournamentwinnerjson.h"
#include "icreatejsonfromtournamentdetails.h"
class DartsModelsServices
{
public:
    IAddPlayerDetailsToTournament *addToTournamentModel() const;
    void setAddToTournamentModel(IAddPlayerDetailsToTournament *newDartsModelManipulator);
    IGetDartsTournamentFromDb *getTournament() const;
    void setGetTournament(IGetDartsTournamentFromDb *newGetTournament);
    IDartsTournamentNumberOfAttempts *getNumberOfAttempts() const;
    void setGetNumberOfAttempts(IDartsTournamentNumberOfAttempts *newGetNumberOfAttempts);
    IModelsDbContext *dartsTournamentDb() const;
    void setDartsTournamentDb(IModelsDbContext *newDartsTournamentDb);
    IGetTournamentWinner *getTournamenWinnerModel() const;
    void setGetTournamenWinnerModel(IGetTournamentWinner *newGetTournamenWinnerModel);
private:
    IModelsDbContext *_dartsTournamentsDb;
    IAddPlayerDetailsToTournament *_addPlayerDetails;
    IGetDartsTournamentFromDb *_getTournament;
    IDartsTournamentNumberOfAttempts *_getNumberOfAttempts;
    IGetTournamentWinner *_getTournamenWinnerModel;
};

#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
