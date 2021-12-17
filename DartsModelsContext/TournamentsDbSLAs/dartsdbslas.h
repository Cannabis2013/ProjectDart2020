#ifndef DARTSTOURNAMENTDBJSONSLAS_H
#define DARTSTOURNAMENTDBJSONSLAS_H
#include "DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h"
#include "DartsModelsContext/TournamentsDbSLAs/idartsbuilder.h"
#include "igetdartstournament.h"
#include "DartsModelsContext/DbSLAs/abstractsavetostorage.h"
#include "DartsModelsContext/DbSLAs/iconverttomodels.h"
#include "DartsModelsContext/DbSLAs/abstractloadmodels.h"
class TnmVals;
class IDartsTournament;
class DartsDbSLAs
{
public:
    typedef IModel<QUuid> Model;
    typedef IDartsTournament DartsModel;
    typedef QByteArray Json;
    typedef IDbContext<Model> DbCtx;
    typedef TnmVals TnmExchanceVals;
    typedef IDartsBuilder<Model,DartsModel,Json,TnmExchanceVals> ModelBuilder;
    typedef IDartsJsonBuilder<Model,Json> JsonBuilder;
    typedef IModelConverter<IModel<QUuid>,Json> ModelConverter;
    typedef AbstractSaveToStorage<Model,Json,DbCtx,ModelConverter> SaveModels;
    typedef AbstractLoadModels<Model,Json> LoadModels;
    ModelBuilder *tournamentBuilder() const {return _tournamentBuilder;}
    void setTournamentBuilder(ModelBuilder *service) {_tournamentBuilder = service;}
    JsonBuilder *tnmJsonBuilder() const {return _tournamentJsonBuilder;}
    void setTournamentJsonBuilder(JsonBuilder *service) {_tournamentJsonBuilder = service;}
    IDbContext<Model> *tnmDbCtx() const {return _dartsDb;}
    void setDartsDbCtx(IDbContext<Model> *service) {_dartsDb = service;}
    IGetDartsTournament<Model,DartsModel> *getTournament() const {return _getTournament;}
    void setGetTournament(IGetDartsTournament<Model,DartsModel> *service) {_getTournament = service;}
    SaveModels *saveToStorage() const {return _saveToStorage;}
    void setSaveToStorage(SaveModels *newDtsDbPersist) {_saveToStorage = newDtsDbPersist;}
    LoadModels *loadFromStorage() const {return _loadFromStorage;}
    void setLoadFromStorage(LoadModels *load) {_loadFromStorage = load;}
private:
    LoadModels *_loadFromStorage;
    SaveModels *_saveToStorage;
    IGetDartsTournament<Model,DartsModel> *_getTournament;
    IDbContext<Model> *_dartsDb;
    ModelBuilder *_tournamentBuilder;
    JsonBuilder *_tournamentJsonBuilder;
};
#endif // MODELSDBJSONSLAS_H
