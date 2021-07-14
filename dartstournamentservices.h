#ifndef DARTSTOURNAMENTSERVICES_H
#define DARTSTOURNAMENTSERVICES_H

#include <idartscreatejsonmetadata.h>
#include <idartsmodelmanipulator.h>
#include <idartstournamentbuilder.h>
#include <idartstournamentjsonbuilder.h>
#include <idartstournamentnumberofattempts.h>
#include <igetdartstournamentdatafromjson.h>
#include <igetdartstournamentfromdb.h>
#include <igetdatafromdartstournament.h>

class DartsTournamentServices
{
public:
    typedef IDartsTournamentBuilder<IDartsTournament,QByteArray> TournamentBuilder;
    IDartsModelManipulator *dartsModelManipulator() const;
    void setDartsModelManipulator(IDartsModelManipulator *newDartsModelManipulator);
    IDartsTournamentJsonBuilder *createJsonFromDartsTournamentModels() const;
    void setCreateJsonFromDartsTournamentModels(IDartsTournamentJsonBuilder *service);
    IGetDartsTournamentFromDb *getTournament() const;
    void setGetTournament(IGetDartsTournamentFromDb *newGetTournament);
    IGetDataFromDartsTournament<ITournament> *getDataFromDartsTournament() const;
    void setGetDataFromDartsTournament(IGetDataFromDartsTournament<ITournament> *newGetDataFromDartsTournament);
    IDartsTournamentNumberOfAttempts *getNumberOfAttempts() const;
    void setGetNumberOfAttempts(IDartsTournamentNumberOfAttempts *newGetNumberOfAttempts);
    IDartsTournamentsDbManipulator *tournamentDbManipulator() const;
    void setTournamentDbManipulator(IDartsTournamentsDbManipulator *newTournamentDbManipulator);
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

private:
    IDartsTournamentsDbManipulator* _tournamentDbManipulator;
    IDartsTournamentDb *_dartsTournamentDb;
    IGetDartsTournamentDataFromJson *_getDartsTournamentDataFromJson;
    TournamentBuilder* _createDartsTournament;
    IAddDetailsToTournamentJson* _dartsTournamentJsonAddDetails;
    IDartsModelManipulator *_dartsModelManipulator;
    IDartsTournamentJsonBuilder *_dartsTournamentCreateJson;
    IGetDartsTournamentFromDb *_getTournament;
    IGetDataFromDartsTournament<ITournament> *_getDataFromDartsTournament;
    IDartsTournamentNumberOfAttempts *_getNumberOfAttempts;
    IDartsCreateJsonMetaData *_createJsonMetaData;
};

#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
