#ifndef DARTSTOURNAMENTSLAS_H
#define DARTSTOURNAMENTSLAS_H

#include "DartsModelsContext/DMCTournamentSLAs/idartscreatejsonmetadata.h"
#include "DartsModelsContext/DMCTournamentSLAs/iaddplayerdetailstotournament.h"
#include "DartsModelsContext/DMCTournamentSLAs/ijsontodartstournamentmodel.h"
#include "DartsModelsContext/DMCTournamentSLAs/idartstournamentjsonbuilder.h"
#include "DartsModelsContext/DMCTournamentSLAs/iextractwinnerinfo.h"
#include "DartsModelsContext/DMCTournamentSLAs/igetdartstournamentfromdb.h"
#include "DartsModelsContext/DMCTournamentSLAs/igettournamentwinner.h"
#include "DartsModelsContext/DMCTournamentSLAs/icreatejsonfromtournamentdetails.h"
class DartsTournamentSLAs
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
    IDartsTournamentExtractor *tournamentExtractor() const;
    void setTournamentExtractor(IDartsTournamentExtractor *newTournamentExtractor);
    IAddDetailsToTournamentJson *dartsTournamentJsonAddDetails() const;
    void setDartsTournamentJsonAddDetails(IAddDetailsToTournamentJson *newDartsTournamentJsonAddDetails);
    IDartsTournamentJsonBuilder *dartsTournamentCreateJson() const;
    void setDartsTournamentCreateJson(IDartsTournamentJsonBuilder *newDartsTournamentCreateJson);
    IExtractWinnerInfo *extractWinnerInfoFromJson() const;
    void setExtractWinnerInfoService(IExtractWinnerInfo *newGetDartsTournamentDataFromJson);
    ICreateJsonFromTournamentDetails *createJsonFromDetails() const;
    void setCreateJsonFromDetails(ICreateJsonFromTournamentDetails *newCreateJsonFromDetails);
    IDartsCreateJsonMetaData *createJsonMetaData() const;
    void setCreateJsonMetaData(IDartsCreateJsonMetaData *newCreateJsonMetaData);
    IJsonToDartsTournamentModel *createDartsTournament() const;
    void setCreateDartsTournament(IJsonToDartsTournamentModel *newCreateDartsTournament);
private:
    IModelsDbContext *_dartsTournamentsDb;
    IAddPlayerDetailsToTournament *_addPlayerDetails;
    IGetDartsTournamentFromDb *_getTournament;
    IGetTournamentWinner *_getTournamenWinnerModel;
    IDartsTournamentExtractor *_tournamentExtractor;
    IAddDetailsToTournamentJson* _dartsTournamentJsonAddDetails;
    IDartsTournamentJsonBuilder *_dartsTournamentCreateJson;
    IExtractWinnerInfo *_extractWinnerInfo;
    ICreateJsonFromTournamentDetails *_createJsonFromDetails;
    IDartsCreateJsonMetaData *_createJsonMetaData;
    IJsonToDartsTournamentModel* _createDartsTournament;
};

#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
