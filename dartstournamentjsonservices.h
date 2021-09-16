#ifndef DARTSTOURNAMENTJSONSERVICES_H
#define DARTSTOURNAMENTJSONSERVICES_H

#include "idartstournamentextractor.h"
#include <iadddetailstotournamentjson.h>
#include <icreatejsonfromtournamentdetails.h>
#include <icreatetournamentwinnerjson.h>
#include <idartscreatejsonmetadata.h>
#include <idartstournamentjsonbuilder.h>
#include <iextractwinnerinfo.h>
#include <ijsontodartstournamentmodel.h>

class DartsTournamentJsonServices
{
public:
    IDartsTournamentExtractor *tournamentExtractor() const;
    void setTournamentExtractor(IDartsTournamentExtractor *newTournamentExtractor);
    IAddDetailsToTournamentJson *dartsTournamentJsonAddDetails() const;
    void setDartsTournamentJsonAddDetails(IAddDetailsToTournamentJson *newDartsTournamentJsonAddDetails);
    IDartsTournamentJsonBuilder *dartsTournamentCreateJson() const;
    void setDartsTournamentCreateJson(IDartsTournamentJsonBuilder *newDartsTournamentCreateJson);
    ICreateTournamentWinnerJson *createTournamentWinnerJson() const;
    void setCreateTournamentWinnerJson(ICreateTournamentWinnerJson *newCreateTournamentWinnerJson);
    IExtractWinnerInfo *extractWinnerInfoFromJson() const;
    void setExtractWinnerInfoService(IExtractWinnerInfo *newGetDartsTournamentDataFromJson);
    ICreateJsonFromTournamentDetails *createJsonFromDetails() const;
    void setCreateJsonFromDetails(ICreateJsonFromTournamentDetails *newCreateJsonFromDetails);
    IDartsCreateJsonMetaData *createJsonMetaData() const;
    void setCreateJsonMetaData(IDartsCreateJsonMetaData *newCreateJsonMetaData);
    IJsonToDartsTournamentModel *createDartsTournament() const;
    void setCreateDartsTournament(IJsonToDartsTournamentModel *newCreateDartsTournament);
private:
    IDartsTournamentExtractor *_tournamentExtractor;
    IAddDetailsToTournamentJson* _dartsTournamentJsonAddDetails;
    IDartsTournamentJsonBuilder *_dartsTournamentCreateJson;
    ICreateTournamentWinnerJson *_createTournamentWinnerJson;
    IExtractWinnerInfo *_extractWinnerInfo;
    ICreateJsonFromTournamentDetails *_createJsonFromDetails;
    IDartsCreateJsonMetaData *_createJsonMetaData;
    IJsonToDartsTournamentModel* _createDartsTournament;
};
#endif // DARTSMODELSJSONSERVICES_H
