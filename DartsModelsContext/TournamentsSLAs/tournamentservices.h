#ifndef TOURNAMENTSERVICES_H
#define TOURNAMENTSERVICES_H
#include "TournamentsSLAs/iwinnerinfobuilder.h"
#include "idartsconsistency.h"
#include "idartscreatemeta.h"
#include "itournamentrepair.h"
#include "igettournamentids.h"
#include "IDartsSetWinner.h"
#include "DbSLAs/imodelconverter.h"
#include "TournamentsDbSLAs/itournamentjsonbuilder.h"
#include "TournamentsDbSLAs/igetdartstournament.h"
#include "TournamentsDbSLAs/idartsbuilder.h"
#include "DbSLAs/idbcontext.h"
class TournamentServices
{
public:
    typedef IModel<QUuid> Model;
    typedef IDbContext<Model> DbCtx;
    typedef IModelConverter<Model> TournamentConverter;
    typedef IDartsJsonBuilder<Model> JsonBuilder;
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
    IDartsConsistency *verifyConsistency() const {return _verifyConsistency;}
    void setVerifyConsistency(IDartsConsistency *service) {_verifyConsistency = service;}
    RepairTournament *tournamentRepair() const {return _tournamentRepair;}
    void setTournamentRepair(RepairTournament *service) {_tournamentRepair = service;}
    TournamentConverter *dartsConverter() const {return _tnmToJson;}
    void setDartsConverter(TournamentConverter *service) {_tnmToJson = service;}
    JsonBuilder *dartsJsonBuilder() const {return _tournamentJsonBuilder;}
    void setDartsJsonBuilder(JsonBuilder *service) {_tournamentJsonBuilder = service;}
    ModelBuilder *tournamentBuilder() const {return _tournamentBuilder;}
    void setTournamentBuilder(ModelBuilder *service) {_tournamentBuilder = service;}
    IDbContext<Model> *dbContext() const {return _dartsDb;}
    void setDartsDbCtx(IDbContext<Model> *service) {_dartsDb = service;}
    GetTournament *getTournament() const {return _getTournament;}
    void setGetTournament(GetTournament *service) {_getTournament = service;}
    SetTournamentWinner *setTnmWinner() const {return _setWinner;}
    void setSetWinner(SetTournamentWinner *service) {_setWinner = service;}
private:
    TournamentConverter *_tnmToJson;
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
};
#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
