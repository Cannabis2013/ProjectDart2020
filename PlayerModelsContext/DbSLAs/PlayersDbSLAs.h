#ifndef PLAYERSDBSLAS_H
#define PLAYERSDBSLAS_H
template<typename T, typename U> class IDuplicateChecker;
template<typename T, typename U> class IGetPlayersFromDb;
template<typename T, typename U, typename V> class ISavePlayers;
template<typename T, typename U, typename V> class IFetchDb;
class IFileDataIO;
template<typename T> class IJsonBuilder;
template<typename T, typename U> class IPlayerBuilder;
class QByteArray;
template<typename T> class IPlayersDbContext;
class IPlayer;

class PlayersDbSLAs
{
public:
    typedef IPlayer Model;
    typedef IPlayersDbContext<Model> DbContext;
    typedef QByteArray Json;
    typedef IPlayerBuilder<Model,Json> PlayerBuilder;
    typedef IJsonBuilder<Model> JsonBuilder;
    typedef IFileDataIO IODevice;
    typedef ISavePlayers<IODevice,DbContext,JsonBuilder> SavePlayers;
    typedef IFetchDb<DbContext,IODevice,PlayerBuilder> FetchDb;
    typedef IDuplicateChecker<Model,DbContext> DupChecker;
    typedef IGetPlayersFromDb<Model,DbContext> GetPlayer;
    DbContext *dbCtx() const {return _dbCtx;}
    void setDbCtx(DbContext *newDbContext) {_dbCtx = newDbContext;}
    JsonBuilder *jsonBuilder() const {return _jsonBuilder;}
    void setJsonBuilder(JsonBuilder *service) {_jsonBuilder = service;}
    PlayerBuilder *playerBuilder() const {return _playerBuilder;}
    void setPlayerBuilder(PlayerBuilder *service) {_playerBuilder = service;}
    GetPlayer *getPlayers() const {return _getPlayersFromDb;}
    void setGetPlayerModelsFromDb(GetPlayer *service) {_getPlayersFromDb = service;}
    SavePlayers *persistDb() const {return _saveToStorage;}
    void setPersistDb(SavePlayers *savePlayers) {_saveToStorage = savePlayers;}
    FetchDb *fetchDb() const {return _fetchDb;}
    void setFetchDb(FetchDb *newLoadFromStorage) {_fetchDb = newLoadFromStorage;}
    DupChecker *dupChk() const {return _dupChk;}
    void setDupChk(DupChecker *newDupChk) {_dupChk = newDupChk;}
    IODevice *ioHandler() const {return _ioHandler;}
    void setIOHandler(IODevice *newSaveToFile) {_ioHandler = newSaveToFile;}
private:
    FetchDb *_fetchDb;
    SavePlayers *_saveToStorage;
    JsonBuilder *_jsonBuilder;
    PlayerBuilder *_playerBuilder;
    IODevice *_ioHandler;
    DbContext *_dbCtx;
    GetPlayer * _getPlayersFromDb;
    DupChecker *_dupChk;
};
#endif // PLAYERSDBSLAS_H
