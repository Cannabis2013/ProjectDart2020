#ifndef DARTSTOURNAMENTSERVICES_H
#define DARTSTOURNAMENTSERVICES_H

#include <idartscreatejsonmetadata.h>
#include <iaddplayerdetailstotournament.h>
#include <icreatemodelfromstring.h>
#include <idartstournamentjsonbuilder.h>
#include <idartstournamentnumberofattempts.h>
#include <iextractwinnerinfo.h>
#include <igetdartstournamentfromdb.h>
#include <igetdatafromdartstournament.h>
#include "igettournamentwinner.h"
#include "icreatetournamentwinnerjson.h"
#include "icreatejsonfromtournamentdetails.h"
class DartsTournamentServices
{
public:
    typedef ICreateModelFromString<AbstractDartsTournament,QByteArray> TournamentBuilder;
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
    IModelsDbContext *dartsTournamentDb() const;
    void setDartsTournamentDb(IModelsDbContext *newDartsTournamentDb);
    IDartsTournamentJsonBuilder *dartsTournamentCreateJson() const;
    void setDartsTournamentCreateJson(IDartsTournamentJsonBuilder *newDartsTournamentCreateJson);
    IAddDetailsToTournamentJson *dartsTournamentJsonAddDetails() const;
    void setDartsTournamentJsonAddDetails(IAddDetailsToTournamentJson *newDartsTournamentJsonAddDetails);
    TournamentBuilder *createDartsTournament() const;
    void setCreateDartsTournament(TournamentBuilder *newCreateDartsTournament);
    IExtractWinnerInfo *extractWinnerInfoFromJson() const;
    void setGetDartsTournamentDataFromJson(IExtractWinnerInfo *newGetDartsTournamentDataFromJson);
    IDartsCreateJsonMetaData *createJsonMetaData() const;
    void setCreateJsonMetaData(IDartsCreateJsonMetaData *newCreateJsonMetaData);
    IGetTournamentWinner *getTournamenWinnerModel() const;
    void setGetTournamenWinnerModel(IGetTournamentWinner *newGetTournamenWinnerModel);
    ICreateTournamentWinnerJson *createTournamentWinnerJson() const;
    void setCreateTournamentWinnerJson(ICreateTournamentWinnerJson *newCreateTournamentWinnerJson);
    ICreateJsonFromTournamentDetails *createJsonFromDetails() const;
    void setCreateJsonFromDetails(ICreateJsonFromTournamentDetails *newCreateJsonFromDetails);

private:
    IModelsDbContext *_dartsTournamentsDb;
    IExtractWinnerInfo *_getDartsTournamentDataFromJson;
    TournamentBuilder* _createDartsTournament;
    IAddDetailsToTournamentJson* _dartsTournamentJsonAddDetails;
    IAddPlayerDetailsToTournament *_addPlayerDetails;
    IDartsTournamentJsonBuilder *_dartsTournamentCreateJson;
    IGetDartsTournamentFromDb *_getTournament;
    IGetDataFromDartsTournament<IModel<QUuid>> *_getDataFromDartsTournament;
    IDartsTournamentNumberOfAttempts *_getNumberOfAttempts;
    IDartsCreateJsonMetaData *_createJsonMetaData;
    IGetTournamentWinner *_getTournamenWinnerModel;
    ICreateTournamentWinnerJson *_createTournamentWinnerJson;
    ICreateJsonFromTournamentDetails *_createJsonFromDetails;
};

#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
