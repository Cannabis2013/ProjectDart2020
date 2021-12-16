#ifndef DARTSSLAS_H
#define DARTSSLAS_H
#include "DartsModelsContext/TournamentsSLAs/isettournamentplayerdetails.h"
#include "DartsModelsContext/TournamentsSLAs/iwinnerinfobuilder.h"
#include "idartsconsistency.h"
#include "idartscreatemeta.h"
#include "itournamentrepair.h"
#include "igettournamentids.h"
#include "iresetdartstournament.h"
#include "DartsModelsContext/DbSLAs/iconverttomodels.h"
class DartsSLAs
{
public:
    typedef IModel<QUuid> Model;
    typedef IDbContext<Model> DbCtx;
    ISetTournamentPlayerDetails *setTournamentPlayerDetails() const {return _addPlayerDetails;}
    void setSetTournamentPlayerDetails(ISetTournamentPlayerDetails *service) {_addPlayerDetails = service;}
    IWinnerInfoBuilder *winnerInfoBuilder() const {return _winnerInfoBuilder;}
    void setWinnerInfoBuilder(IWinnerInfoBuilder *service) {_winnerInfoBuilder = service;}
    IGetDartsTournamentIds<Model,DbCtx> *getTournamentIds() const {return _getTournamentIds;}
    void setGetTournamentIds(IGetDartsTournamentIds<Model,DbCtx> *newGetTournamentIds) {_getTournamentIds = newGetTournamentIds;}
    IDartsCreateMeta *createMeta() const {return _createMeta;}
    void setCreateMeta(IDartsCreateMeta *builder) {_createMeta = builder;}
    IResetDartsTournament<Model> *resetDarts() const {return _resetTournament;}
    void setResetTournament(IResetDartsTournament<Model> *newResetTournament) {_resetTournament = newResetTournament;}
    IDartsConsistency *verifyConsistency() const {return _verifyConsistency;}
    void setVerifyConsistency(IDartsConsistency *newVerifyConsistency) {_verifyConsistency = newVerifyConsistency;}
    ITournamentRepair *tournamentRepair() const {return _tournamentRepair;}
    void setTournamentRepair(ITournamentRepair *newTournamentRepair) {_tournamentRepair = newTournamentRepair;}
    IConvertToModels<QByteArray, Model> *toDartsModels() const {return _toDartsModels;}
    void setToDartsModels(IConvertToModels<QByteArray, Model> *newToDartsModels) {_toDartsModels = newToDartsModels;}
private:
    IConvertToModels<QByteArray,Model> *_toDartsModels;
    IResetDartsTournament<Model> *_resetTournament;
    IDartsCreateMeta *_createMeta;
    IGetDartsTournamentIds<Model,DbCtx> *_getTournamentIds;
    ISetTournamentPlayerDetails *_addPlayerDetails;
    IWinnerInfoBuilder *_winnerInfoBuilder;
    IDartsConsistency *_verifyConsistency;
    ITournamentRepair *_tournamentRepair;
};
#endif // DARTSTOURNAMENTSERVICESPROVIDER_H
