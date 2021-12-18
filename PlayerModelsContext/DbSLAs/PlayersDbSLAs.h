#ifndef PLAYERSDBSLAS_H
#define PLAYERSDBSLAS_H
#include "IPlayersDbContext.h"
#include "igetplayerfromdb.h"
#include "iplayerbuilder.h"
#include "iplayer.h"
#include "ifetchdb.h"
#include "ModelsSLAs/iduplicatechecker.h"
#include "DataSLAs/idatabuilder.h"
#include "DbSLAs/isaveplayers.h"
#include "IOSLAs/ifiledataio.h"
class PlayersDbSLAs
{
public:
    typedef IPlayer Model;
    typedef IPlayersDbContext<Model> DbCtx;
    typedef QByteArray Json;
    typedef IPlayerBuilder<Model,Json> PlayerBuilder;
    typedef IDataBuilder<Model,QByteArray> JsonBuilder;
    typedef IFileDataIO<QByteArray> IODevice;
    typedef ISavePlayers<IODevice,DbCtx,JsonBuilder> SavePlayers;
    typedef IFetchDb<DbCtx,IODevice,PlayerBuilder> FetchDb;
    DbCtx *dbCtx() const {return _dbCtx;}
    void setDbCtx(DbCtx *newDbContext) {_dbCtx = newDbContext;}
    JsonBuilder *jsonBuilder() const {return _jsonBuilder;}
    void setJsonBuilder(JsonBuilder *service) {_jsonBuilder = service;}
    IPlayerBuilder<Model,QByteArray> *playerBuilder() const {return _playerBuilder;}
    void setPlayerBuilder(IPlayerBuilder<Model,QByteArray> *service) {_playerBuilder = service;}
    IGetPlayersFromDb<Model,DbCtx> *getPlayers() const {return _getPlayersFromDb;}
    void setGetPlayerModelsFromDb(IGetPlayersFromDb<Model,DbCtx> *service) {_getPlayersFromDb = service;}
    SavePlayers *persistDb() const {return _saveToStorage;}
    void setPersistDb(SavePlayers *savePlayers) {_saveToStorage = savePlayers;}
    FetchDb *fetchDb() const {return _fetchDb;}
    void setFetchDb(FetchDb *newLoadFromStorage) {_fetchDb = newLoadFromStorage;}
    IDuplicateChecker<Model,DbCtx> *dupChk() const {return _dupChk;}
    void setDupChk(IDuplicateChecker<Model,DbCtx> *newDupChk) {_dupChk = newDupChk;}
    IODevice *ioHandler() const {return _ioHandler;}
    void setIOHandler(IODevice *newSaveToFile) {_ioHandler = newSaveToFile;}
private:
    FetchDb *_fetchDb;
    SavePlayers *_saveToStorage;
    JsonBuilder *_jsonBuilder;
    PlayerBuilder *_playerBuilder;
    IODevice *_ioHandler;
    DbCtx *_dbCtx;
    IGetPlayersFromDb<Model,DbCtx> * _getPlayersFromDb;
    IDuplicateChecker<Model,DbCtx> *_dupChk;
};
#endif // PLAYERSDBSLAS_H
