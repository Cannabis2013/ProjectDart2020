#ifndef DARTSSERVICES_H
#define DARTSSERVICES_H
#include "TournamentsSLAs/iwinnerinfobuilder.h"
#include "idartsconsistency.h"
#include "idartscreatemeta.h"
#include "itournamentrepair.h"
#include "igettournamentids.h"
#include "IDartsSetWinner.h"
#include "idartscreatetournament.h"
#include "IDartsRemoveTournaments.h"
#include "idartsresettournament.h"
#include "DbSLAs/iconvertfromdata.h"
#include "DbSLAs/imodelconverter.h"
#include "DbSLAs/idbjsonbuilder.h"
#include "TournamentsDbSLAs/itournamentjsonbuilder.h"
#include "TournamentsDbSLAs/igetdartstournament.h"
#include "TournamentsDbSLAs/idartsbuilder.h"
#include "DbSLAs/idbcontext.h"
class DartsServices
{
public:
    typedef IModel<QUuid> Model;
    typedef IDbContext<Model> DbCtx;
    typedef IDbJsonBuilder<Model> TournamentsToJson;
    typedef IModelConverter<Model> TournamentToJson;
    typedef IDartsCreateTournament<Model> CreateTournament;
    typedef IDartsJsonBuilder<Model> JsonBuilder;
    typedef IConvertFromData<Model> ConvertFromByteArray;
    typedef IDartsBuilder<Model> ModelBuilder;
    typedef ITournamentRepair<Model> RepairTournament;
    typedef IGetDartsTournament<Model> GetTournament;
    typedef IDartsSetWinner<Model> SetTournamentWinner;
    IWinnerInfoBuilder *winnerInfoBuilder() const {return _winnerInfoBuilder;}
    void setWinnerInfoBuilder(IWinnerInfoBuilder *service) {_winnerInfoBuilder = service;}
    IGetDartsTournamentIds<Model,DbCtx> *getTournamentIds() const {return _getTournamentIds;}
    void setGetTournamentIds(IGetDartsTournamentIds<Model,DbCtx> *service) {_getTournamentIds = service;}
    IDartsCreateMeta *createMeta() const {return _createMeta;}
    void setCreateMeta(IDartsCreateMeta *builder) {_createMeta = builder;}
    IDartsResetTournament *resetDarts() const {return _resetTournament;}
    void setResetTournament(IDartsResetTournament *service) {_resetTournament = service;}
    IDartsConsistency *verifyConsistency() const {return _verifyConsistency;}
    void setVerifyConsistency(IDartsConsistency *service) {_verifyConsistency = service;}
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
    CreateTournament *createTournament() const {return _createTournament;}
    void setCreateTournament(CreateTournament *service) {_createTournament = service;}
    IDartsRemoveTournaments *removeTournaments() const {return _removeTournaments;}
    void setRemoveTournaments(IDartsRemoveTournaments *service) {_removeTournaments = service;}
private:
    TournamentsToJson *_dartsConverter;
    TournamentToJson *_tnmToJson;
    ConvertFromByteArray *_jsonToTournaments;
    IDartsResetTournament *_resetTournament;
    IDartsCreateMeta *_createMeta;
    IGetDartsTournamentIds<Model,DbCtx> *_getTournamentIds;
    IWinnerInfoBuilder *_winnerInfoBuilder;
    IDartsConsistency *_verifyConsistency;
    RepairTournament *_tournamentRepair;
    JsonBuilder *_tournamentJsonBuilder;
    GetTournament *_getTournament;
    IDbContext<Model> *_dartsDb;
    ModelBuilder *_tournamentBuilder;
    SetTournamentWinner *_setWinner;
    CreateTournament*_createTournament;
    IDartsRemoveTournaments *_removeTournaments;
};
#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
