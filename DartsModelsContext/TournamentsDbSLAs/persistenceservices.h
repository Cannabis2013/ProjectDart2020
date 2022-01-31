#ifndef PERSISTENCESERVICES_H
#define PERSISTENCESERVICES_H
#include <qjsonobject.h>
#include "DbSLAs/idartspersist.h"
#include "TournamentsDbSLAs/itournamentjsonbuilder.h"
#include "TournamentsDbSLAs/idartsbuilder.h"
#include "igetdartstournament.h"
#include "DbSLAs/abstractsavetostorage.h"
#include "DbSLAs/iconvertfromdata.h"
#include "DbSLAs/abstractloadmodels.h"
struct TnmVals;
class IDartsTournament;
class PersistenceServices
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
    IDartsPersist *persist() const {return _persist;}
    void setPersist(IDartsPersist *newPersist) {_persist = newPersist;}
private:
    IODevice *_ioDevice;
    LoadModels *_loadFromStorage;
    SaveModels *_saveToStorage;
    IDartsPersist *_persist;
};
#endif // MODELSDBJSONSLAS_H
