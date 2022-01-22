#ifndef DARTSTOURNAMENTDBJSONSLAS_H
#define DARTSTOURNAMENTDBJSONSLAS_H
#include <qjsonobject.h>
#include "TournamentsDbSLAs/itournamentjsonbuilder.h"
#include "TournamentsDbSLAs/idartsbuilder.h"
#include "igetdartstournament.h"
#include "DbSLAs/abstractsavetostorage.h"
#include "DbSLAs/iconvertfromdata.h"
#include "DbSLAs/abstractloadmodels.h"
struct TnmVals;
class IDartsTournament;
class PersistenceSLAs
{
public:
    typedef IModel<QUuid> BaseModel;
    typedef IDartsTournament SuperModel;
    typedef IDartsTournament DartsModel;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IDbContext<BaseModel> DbCtx;
    typedef IFileDataIO<ByteArray> IODevice;
    typedef IDartsBuilder<BaseModel> ModelBuilder;
    typedef IDartsJsonBuilder<BaseModel> JsonBuilder;
    typedef IModelConverter<BaseModel> ModelConverter;
    typedef AbstractSaveToStorage<BaseModel> SaveModels;
    typedef AbstractLoadModels<BaseModel> LoadModels;
    SaveModels *saveToStorage() const {return _saveToStorage;}
    void setSaveToStorage(SaveModels *newDtsDbPersist) {_saveToStorage = newDtsDbPersist;}
    LoadModels *loadFromStorage() const {return _loadFromStorage;}
    void setLoadFromStorage(LoadModels *load) {_loadFromStorage = load;}
    IODevice *ioDevice() const {return _ioDevice;}
    void setIoDevice(IODevice *newIoDevice) {_ioDevice = newIoDevice;}
private:
    IODevice *_ioDevice;
    LoadModels *_loadFromStorage;
    SaveModels *_saveToStorage;
};
#endif // MODELSDBJSONSLAS_H
