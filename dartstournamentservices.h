#ifndef DARTSTOURNAMENTSERVICES_H
#define DARTSTOURNAMENTSERVICES_H

#include <idartscreatejsonmetadata.h>
#include <iaddplayerdetailstotournament.h>
#include <idartstournamentbuilder.h>
#include <idartstournamentjsonbuilder.h>
#include <idartstournamentnumberofattempts.h>
#include <igetdartstournamentdatafromjson.h>
#include <igetdartstournamentfromdb.h>
#include <igetdatafromdartstournament.h>
#include "igettournamentwinner.h"
#include "isettournamentwinnerid.h"
#include "icreatetournamentwinnerjson.h"

class DartsTournamentServices
{
public:
    typedef IDartsTournamentBuilder<IDartsTournament,QByteArray> TournamentBuilder;
    IAddPlayerDetailsToTournament *addToTournamentModel() const;
    void setAddToTournamentModel(IAddPlayerDetailsToTournament *newDartsModelManipulator);
    IDartsTournamentJsonBuilder *createJsonFromDartsTournamentModels() const;
    void setCreateJsonFromDartsTournamentModels(IDartsTournamentJsonBuilder *service);
    IGetDartsTournamentFromDb *getTournament() const;
    void setGetTournament(IGetDartsTournamentFromDb *newGetTournament);
    IGetDataFromDartsTournament<ITournament> *getDataFromDartsTournament() const;
    void setGetDataFromDartsTournament(IGetDataFromDartsTournament<ITournament> *newGetDataFromDartsTournament);
    IDartsTournamentNumberOfAttempts *getNumberOfAttempts() const;
    void setGetNumberOfAttempts(IDartsTournamentNumberOfAttempts *newGetNumberOfAttempts);
    IRemoveTournamentsFromDb *tournamentDbManipulator() const;
    void setTournamentDbManipulator(IRemoveTournamentsFromDb *newTournamentDbManipulator);
    IDartsTournamentDb *dartsTournamentDb() const;
    void setDartsTournamentDb(IDartsTournamentDb *newDartsTournamentDb);
    IDartsTournamentJsonBuilder *dartsTournamentCreateJson() const;
    void setDartsTournamentCreateJson(IDartsTournamentJsonBuilder *newDartsTournamentCreateJson);
    IAddDetailsToTournamentJson *dartsTournamentJsonAddDetails() const;
    void setDartsTournamentJsonAddDetails(IAddDetailsToTournamentJson *newDartsTournamentJsonAddDetails);
    TournamentBuilder *createDartsTournament() const;
    void setCreateDartsTournament(TournamentBuilder *newCreateDartsTournament);
    IGetDartsTournamentDataFromJson *getDartsTournamentDataFromJson() const;
    void setGetDartsTournamentDataFromJson(IGetDartsTournamentDataFromJson *newGetDartsTournamentDataFromJson);
    IDartsCreateJsonMetaData *createJsonMetaData() const;
    void setCreateJsonMetaData(IDartsCreateJsonMetaData *newCreateJsonMetaData);
    IGetTournamentWinner *getTournamenWinnerModel() const;
    void setGetTournamenWinnerModel(IGetTournamentWinner *newGetTournamenWinnerModel);

    ISetTournamentWinnerId *setTournamentWinnerId() const;
    void setSetTournamentWinnerId(ISetTournamentWinnerId *newSetTournamentWinnerId);

    ICreateTournamentWinnerJson *createTournamentWinnerJson() const;
    void setCreateTournamentWinnerJson(ICreateTournamentWinnerJson *newCreateTournamentWinnerJson);

private:
    IRemoveTournamentsFromDb* _removeTournamentsByIndexes;
    IDartsTournamentDb *_dartsTournamentDb;
    IGetDartsTournamentDataFromJson *_getDartsTournamentDataFromJson;
    TournamentBuilder* _createDartsTournament;
    IAddDetailsToTournamentJson* _dartsTournamentJsonAddDetails;
    IAddPlayerDetailsToTournament *_dartsModelManipulator;
    IDartsTournamentJsonBuilder *_dartsTournamentCreateJson;
    IGetDartsTournamentFromDb *_getTournament;
    IGetDataFromDartsTournament<ITournament> *_getDataFromDartsTournament;
    IDartsTournamentNumberOfAttempts *_getNumberOfAttempts;
    IDartsCreateJsonMetaData *_createJsonMetaData;
    IGetTournamentWinner *_getTournamenWinnerModel;
    ISetTournamentWinnerId *_setTournamentWinnerId;
    ICreateTournamentWinnerJson *_createTournamentWinnerJson;
};

#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
