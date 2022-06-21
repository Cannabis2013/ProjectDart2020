#ifndef TOURNAMENTSERVICES_H
#define TOURNAMENTSERVICES_H

#include "idartsconsistency.h"
#include "idartscreatemeta.h"
#include "igettournamentids.h"
#include "iwinnerinfobuilder.h"
#include <DartsModelsContext/Contracts/Db/idbcontext.h>
#include <DartsModelsContext/Contracts/Db/imodelconverter.h>
#include <DartsModelsContext/Contracts/Tournament/idartsbuilder.h>
#include <DartsModelsContext/Contracts/Tournament/igetdartstournament.h>
#include <DartsModelsContext/Contracts/Routines/IDartsSetWinner.h>

template<typename T> class IModel;

class TournamentServices
{
public:
        typedef IModel<QUuid> Model;
        typedef IDbContext<Model> DbCtx;
        typedef IModelConverter<Model> TournamentConverter;
        typedef IDartsBuilder<Model> ModelBuilder;
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
        TournamentConverter *dartsConverter() const {return _tnmToJson;}
        void setDartsConverter(TournamentConverter *service) {_tnmToJson = service;}
        ModelBuilder *tournamentBuilder() const {return _tournamentBuilder;}
        void setTournamentBuilder(ModelBuilder *service) {_tournamentBuilder = service;}
        IDbContext<Model> *dbContext() const {return _dartsDb;}
        void setDartsDbCtx(IDbContext<Model> *service) {_dartsDb = service;}
        GetTournament *getTournament() const {return _getTournament;}
        void setGetTournament(GetTournament *service) {_getTournament = service;}
private:
        TournamentConverter *_tnmToJson;
        IDartsCreateMeta *_createMeta;
        IGetDartsTournamentIds<Model,DbCtx> *_getTournamentIds;
        IWinnerInfoBuilder *_winnerInfoBuilder;
        IDartsConsistency *_verifyConsistency;
        GetTournament *_getTournament;
        IDbContext<Model> *_dartsDb;
        ModelBuilder *_tournamentBuilder;
};
#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
