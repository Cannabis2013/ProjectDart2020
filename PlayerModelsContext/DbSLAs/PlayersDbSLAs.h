#ifndef PLAYERSDBSLAS_H
#define PLAYERSDBSLAS_H
#include "IPlayersDbContext.h"
#include "igetplayerfromdb.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "ModelsContext/DbSLAs/ipersistmemdb.h"
#include <ModelsContext/DbSLAs/abstractloadfromstorage.h>
class PlayersDbSLAs
{
public:
    typedef IModel<QUuid> BaseModel;
    typedef QByteArray JsonFormat;
    IPlayersDbContext *dbContext() const {return _dbContext;}
    void setDbContext(IPlayersDbContext *newDbContext) {_dbContext = newDbContext;}
    IPlayerJsonBuilder<BaseModel,QByteArray> *jsonBuilder() const {return _jsonBuilder;}
    void setJsonBuilder(IPlayerJsonBuilder<BaseModel,QByteArray> *service) {_jsonBuilder = service;}
    IPlayerBuilder<BaseModel,QByteArray> *playerBuilder() const {return _playerBuilder;}
    void setPlayerBuilder(IPlayerBuilder<BaseModel,QByteArray> *service) {_playerBuilder = service;}
    IGetPlayersFromDb *getPlayers() const {return _getPlayerModelsFromDb;}
    void setGetPlayerModelsFromDb(IGetPlayersFromDb *service) {_getPlayerModelsFromDb = service;}
    IPersistMemDb<IModel<QUuid>, QByteArray> *persistDbCtx() const {return _saveToStorage;}
    void setPersistDbCtx(IPersistMemDb<IModel<QUuid>, QByteArray> *saveToStorage) {_saveToStorage = saveToStorage;}
    AbstractLoadFromStorage<BaseModel, JsonFormat> *loadFromStorage() const {return _loadFromStorage;}
    void setLoadFromStorage(AbstractLoadFromStorage<BaseModel, JsonFormat> *newLoadFromStorage) {_loadFromStorage = newLoadFromStorage;}
private:
    AbstractLoadFromStorage<BaseModel,JsonFormat> *_loadFromStorage;
    IPersistMemDb<BaseModel,QByteArray> *_saveToStorage;
    IPlayerJsonBuilder<BaseModel,QByteArray> *_jsonBuilder;
    IPlayerBuilder<BaseModel,QByteArray> *_playerBuilder;
    IPlayersDbContext *_dbContext;
    IGetPlayersFromDb * _getPlayerModelsFromDb;
};
#endif // PLAYERSDBSLAS_H
