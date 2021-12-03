#ifndef DARTSTOURNAMENTDBJSONSLAS_H
#define DARTSTOURNAMENTDBJSONSLAS_H
#include "DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h"
#include "DartsModelsContext/TournamentsDbSLAs/idartsbuilder.h"
#include "igetdartstournament.h"
#include "ModelsContext/DbSLAs/abstractsavetostorage.h"
#include "ModelsContext/DbSLAs/icreatemodelsfrom.h"
#include "ModelsContext/DbSLAs/abstractloadfromstorage.h"
class DartsDbSLAs
{
public:
    typedef IModel<QUuid> BaseModel;
    typedef AbstractDartsTournament DartsModel;
    typedef QByteArray JsonFormat;
    IDartsBuilder<BaseModel,DartsModel> *tournamentBuilder() const {return _tournamentBuilder;}
    void setTournamentBuilder(IDartsBuilder<BaseModel,DartsModel> *service) {_tournamentBuilder = service;}
    IDartsJsonBuilder<BaseModel,JsonFormat> *dtsJsonBuilder() const {return _tournamentJsonBuilder;}
    void setTournamentJsonBuilder(IDartsJsonBuilder<BaseModel,JsonFormat> *service) {_tournamentJsonBuilder = service;}
    IDbContext<BaseModel> *dartsDbCtx() const {return _dartsDb;}
    void setDartsDbCtx(IDbContext<BaseModel> *service) {_dartsDb = service;}
    IGetDartsTournament<BaseModel,DartsModel> *getTournament() const {return _getTournament;}
    void setGetTournament(IGetDartsTournament<BaseModel,DartsModel> *service) {_getTournament = service;}
    AbstractSaveToStorage<BaseModel, JsonFormat> *saveToStorage() const {return _saveToStorage;}
    void setSaveToStorage(AbstractSaveToStorage<BaseModel, JsonFormat> *newDtsDbPersist) {_saveToStorage = newDtsDbPersist;}
    AbstractLoadFromStorage<BaseModel, JsonFormat> *loadFromStorage() const {return _loadFromStorage;}
    void setLoadFromStorage(AbstractLoadFromStorage<BaseModel, JsonFormat> *load) {_loadFromStorage = load;}
private:
    AbstractLoadFromStorage<BaseModel,JsonFormat> *_loadFromStorage;
    AbstractSaveToStorage<BaseModel,JsonFormat> *_saveToStorage;
    IGetDartsTournament<BaseModel,DartsModel> *_getTournament;
    IDbContext<BaseModel> *_dartsDb;
    IDartsBuilder<BaseModel,DartsModel> *_tournamentBuilder;
    IDartsJsonBuilder<BaseModel,JsonFormat> *_tournamentJsonBuilder;
};
#endif // MODELSDBJSONSLAS_H
