#ifndef DARTSTOURNAMENTSERVICES_H
#define DARTSTOURNAMENTSERVICES_H

#include <idartscreatejsonmetadata.h>
#include <iaddplayerdetailstotournament.h>
#include <icreatemodelfromstring.h>
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
    typedef ICreateModelFromString<IDartsTournament,QByteArray> TournamentBuilder;
    IAddPlayerDetailsToTournament *addToTournamentModel() const;
    void setAddToTournamentModel(IAddPlayerDetailsToTournament *newDartsModelManipulator);
    IDartsTournamentJsonBuilder *createJsonFromDartsTournamentModels() const;
    void setCreateJsonFromDartsTournamentModels(IDartsTournamentJsonBuilder *service);
    IGetDartsTournamentFromDb *getTournament() const;
    void setGetTournament(IGetDartsTournamentFromDb *newGetTournament);
    IGetDataFromDartsTournament<IModel<QUuid> > *getDataFromDartsTournament() const;
    void setGetDataFromDartsTournament(IGetDataFromDartsTournament<IModel<QUuid> > *newGetDataFromDartsTournament);
    IDartsTournamentNumberOfAttempts *getNumberOfAttempts() const;
    void setGetNumberOfAttempts(IDartsTournamentNumberOfAttempts *newGetNumberOfAttempts);
    IDbService *dartsTournamentDb() const;
    void setDartsTournamentDb(IDbService *newDartsTournamentDb);
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
    IDbService *_dartsTournamentsDb;
    IGetDartsTournamentDataFromJson *_getDartsTournamentDataFromJson;
    TournamentBuilder* _createDartsTournament;
    IAddDetailsToTournamentJson* _dartsTournamentJsonAddDetails;
    IAddPlayerDetailsToTournament *_addPlayerDetails;
    IDartsTournamentJsonBuilder *_dartsTournamentCreateJson;
    IGetDartsTournamentFromDb *_getTournament;
    IGetDataFromDartsTournament<IModel<QUuid>> *_getDataFromDartsTournament;
    IDartsTournamentNumberOfAttempts *_getNumberOfAttempts;
    IDartsCreateJsonMetaData *_createJsonMetaData;
    IGetTournamentWinner *_getTournamenWinnerModel;
    ISetTournamentWinnerId *_setTournamentWinnerId;
    ICreateTournamentWinnerJson *_createTournamentWinnerJson;
};

#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
