#ifndef DARTSTOURNAMENTMODELSSERVICES_H
#define DARTSTOURNAMENTMODELSSERVICES_H

#include "DartsTournamentJsonServices/idartscreatejsonmetadata.h"
#include "iaddplayerdetailstotournament.h"
#include "DartsTournamentJsonServices/ijsontodartstournamentmodel.h"
#include "DartsTournamentJsonServices/idartstournamentjsonbuilder.h"
#include "DartsTournamentJsonServices/iextractwinnerinfo.h"
#include "igetdartstournamentfromdb.h"
#include "igettournamentwinner.h"
#include "DartsTournamentJsonServices/icreatetournamentwinnerjson.h"
#include "DartsTournamentJsonServices/icreatejsonfromtournamentdetails.h"
class DartsTournamentModelsServices
{
public:
    IAddPlayerDetailsToTournament *addToTournamentModel() const;
    void setAddToTournamentModel(IAddPlayerDetailsToTournament *newDartsModelManipulator);
    IGetDartsTournamentFromDb *getTournament() const;
    void setGetTournament(IGetDartsTournamentFromDb *newGetTournament);
    IModelsDbContext *dartsTournamentDb() const;
    void setDartsTournamentDb(IModelsDbContext *newDartsTournamentDb);
    IGetTournamentWinner *getTournamenWinnerModel() const;
    void setGetTournamenWinnerModel(IGetTournamentWinner *newGetTournamenWinnerModel);
private:
    IModelsDbContext *_dartsTournamentsDb;
    IAddPlayerDetailsToTournament *_addPlayerDetails;
    IGetDartsTournamentFromDb *_getTournament;
    IGetTournamentWinner *_getTournamenWinnerModel;
};

#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
