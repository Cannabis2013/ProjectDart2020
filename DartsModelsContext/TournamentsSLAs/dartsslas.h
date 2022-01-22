#ifndef DARTSSLAS_H
#define DARTSSLAS_H
#include "TournamentsSLAs/isettournamentplayerdetails.h"
#include "TournamentsSLAs/iwinnerinfobuilder.h"
#include "idartsconsistency.h"
#include "idartscreatemeta.h"
#include "itournamentrepair.h"
#include "igettournamentids.h"
#include "iresetdartstournament.h"
#include "IDartsSetWinner.h"
#include "DbSLAs/iconvertfromdata.h"
#include "DbSLAs/imodelconverter.h"
#include "DbSLAs/idbjsonbuilder.h"
#include "TournamentsDbSLAs/itournamentjsonbuilder.h"
#include "TournamentsDbSLAs/igetdartstournament.h"
#include "TournamentsDbSLAs/idartsbuilder.h"
class DartsSLAs
{
public:
    typedef IModel<QUuid> Model;
    typedef IDartsTournament DartsModel;
    typedef IDbContext<Model> DbCtx;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IDbJsonBuilder<Model> TournamentsToJson;
    typedef IModelConverter<Model> TournamentToJson;
    typedef IDartsJsonBuilder<Model> JsonBuilder;
    typedef IConvertFromData<Model> ConvertFromByteArray;
    typedef IDartsBuilder<Model> ModelBuilder;
    typedef IDartsConsistency<Model> VerifyConsistency;
    typedef ITournamentRepair<Model> RepairTournament;
    typedef IGetDartsTournament<Model> GetTournament;
    typedef IDartsSetWinner<Model> SetTournamentWinner;
    ISetTournamentPlayerDetails *setTournamentPlayerDetails() const {return _addPlayerDetails;}
    void setSetTournamentPlayerDetails(ISetTournamentPlayerDetails *service) {_addPlayerDetails = service;}
    IWinnerInfoBuilder *winnerInfoBuilder() const {return _winnerInfoBuilder;}
    void setWinnerInfoBuilder(IWinnerInfoBuilder *service) {_winnerInfoBuilder = service;}
    IGetDartsTournamentIds<Model,DbCtx> *getTournamentIds() const {return _getTournamentIds;}
    void setGetTournamentIds(IGetDartsTournamentIds<Model,DbCtx> *service) {_getTournamentIds = service;}
    IDartsCreateMeta *createMeta() const {return _createMeta;}
    void setCreateMeta(IDartsCreateMeta *builder) {_createMeta = builder;}
    IResetDartsTournament<Model> *resetDarts() const {return _resetTournament;}
    void setResetTournament(IResetDartsTournament<Model> *service) {_resetTournament = service;}
    VerifyConsistency *verifyConsistency() const {return _verifyConsistency;}
    void setVerifyConsistency(VerifyConsistency *service) {_verifyConsistency = service;}
    RepairTournament *tournamentRepair() const {return _tournamentRepair;}
    void setTournamentRepair(RepairTournament *service) {_tournamentRepair = service;}
    ConvertFromByteArray *jsonToTournaments() const {return _jsonToTournaments;}
    void setJsonToTournaments(ConvertFromByteArray *service) {_jsonToTournaments = service;}
    TournamentToJson *dartsConverter() const {return _tnmToJson;}
    void setDartsConverter(TournamentToJson *service) {_tnmToJson = service;}
    TournamentsToJson *tournamentsToJson() const {return _dartsConverter;}
    void setTournamentsToJson(TournamentsToJson *service) {_dartsConverter = service;}
    JsonBuilder *dartsJsonBuilder() const {return _tournamentJsonBuilder;}
    void setDartsJsonBuilder(JsonBuilder *service) {_tournamentJsonBuilder = service;}
    ModelBuilder *tournamentBuilder() const {return _tournamentBuilder;}
    void setTournamentBuilder(ModelBuilder *service) {_tournamentBuilder = service;}
    IDbContext<Model> *dartsDbCtx() const {return _dartsDb;}
    void setDartsDbCtx(IDbContext<Model> *service) {_dartsDb = service;}
    GetTournament *getTournament() const {return _getTournament;}
    void setGetTournament(GetTournament *service) {_getTournament = service;}
    SetTournamentWinner *setTnmWinner() const {return _setWinner;}
    void setSetWinner(SetTournamentWinner *service) {_setWinner = service;}
private:
    TournamentsToJson *_dartsConverter;
    TournamentToJson *_tnmToJson;
    ConvertFromByteArray *_jsonToTournaments;
    IResetDartsTournament<Model> *_resetTournament;
    IDartsCreateMeta *_createMeta;
    IGetDartsTournamentIds<Model,DbCtx> *_getTournamentIds;
    ISetTournamentPlayerDetails *_addPlayerDetails;
    IWinnerInfoBuilder *_winnerInfoBuilder;
    VerifyConsistency *_verifyConsistency;
    RepairTournament *_tournamentRepair;
    JsonBuilder *_tournamentJsonBuilder;
    GetTournament *_getTournament;
    IDbContext<Model> *_dartsDb;
    ModelBuilder *_tournamentBuilder;
    SetTournamentWinner *_setWinner;
};
#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
