#ifndef PLAYERSDBSLAS_H
#define PLAYERSDBSLAS_H
#include "IPlayersDbContext.h"
#include "igetplayerfromdb.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "ModelsContext/DbSLAs/abstractsavetostorage.h"
#include "ModelsContext/DbSLAs/abstractloadfromstorage.h"
#include "PlayerModelsContext/ModelsSLAs/iduplicatechecker.h"
class PlayersDbSLAs
{
public:
    typedef IModel<QUuid> BaseModel;
    typedef QByteArray JsonFormat;
    IPlayersDbContext *dbCtx() const {return _dbCtx;}
    void setDbCtx(IPlayersDbContext *newDbContext) {_dbCtx = newDbContext;}
    IPlayerJsonBuilder<BaseModel,QByteArray> *jsonBuilder() const {return _jsonBuilder;}
    void setJsonBuilder(IPlayerJsonBuilder<BaseModel,QByteArray> *service) {_jsonBuilder = service;}
    IPlayerBuilder<BaseModel,QByteArray> *playerBuilder() const {return _playerBuilder;}
    void setPlayerBuilder(IPlayerBuilder<BaseModel,QByteArray> *service) {_playerBuilder = service;}
    IGetPlayersFromDb *getPlayers() const {return _getPlayersFromDb;}
    void setGetPlayerModelsFromDb(IGetPlayersFromDb *service) {_getPlayersFromDb = service;}
    AbstractSaveToStorage<IModel<QUuid>, QByteArray> *persistDbCtx() const {return _saveToStorage;}
    void setPersistDbCtx(AbstractSaveToStorage<IModel<QUuid>, QByteArray> *saveToStorage) {_saveToStorage = saveToStorage;}
    AbstractLoadFromStorage<BaseModel, JsonFormat> *loadFromStorage() const {return _loadFromStorage;}
    void setLoadFromStorage(AbstractLoadFromStorage<BaseModel, JsonFormat> *newLoadFromStorage) {_loadFromStorage = newLoadFromStorage;}
    IDuplicateChecker *dupChk() const;
    void setDupChk(IDuplicateChecker *newDupChk);
private:
    AbstractLoadFromStorage<BaseModel,JsonFormat> *_loadFromStorage;
    AbstractSaveToStorage<BaseModel,QByteArray> *_saveToStorage;
    IPlayerJsonBuilder<BaseModel,QByteArray> *_jsonBuilder;
    IPlayerBuilder<BaseModel,QByteArray> *_playerBuilder;
    IPlayersDbContext *_dbCtx;
    IGetPlayersFromDb * _getPlayersFromDb;
    IDuplicateChecker *_dupChk;
};
inline IDuplicateChecker *PlayersDbSLAs::dupChk() const
{
    return _dupChk;
}

inline void PlayersDbSLAs::setDupChk(IDuplicateChecker *newDupChk)
{
    _dupChk = newDupChk;
}
#endif // PLAYERSDBSLAS_H
