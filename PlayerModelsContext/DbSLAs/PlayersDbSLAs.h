#ifndef PLAYERSDBSLAS_H
#define PLAYERSDBSLAS_H

#include "IPlayersDbContext.h"
#include "igetplayerfromdb.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"

class PlayersDbSLAs
{
public:
    IPlayersDbContext *dbContext() const
    {
        return _dbContext;
    }
    void setDbContext(IPlayersDbContext *newDbContext)
    {
        _dbContext = newDbContext;
    }
    IPlayerContextJsonBuilder *jsonBuilder() const
    {
        return _jsonBuilder;
    }
    void setJsonBuilder(IPlayerContextJsonBuilder *service)
    {
        _jsonBuilder = service;
    }
    IPlayerContextModelBuilder *playerBuilder() const
    {
        return _modelBuilder;
    }
    void setPlayerBuilder(IPlayerContextModelBuilder *service)
    {
        _modelBuilder = service;
    }
    IGetPlayersFromDb *getPlayerModelsFromDb() const
    {
        return _getPlayerModelsFromDb;
    }
    void setGetPlayerModelsFromDb(IGetPlayersFromDb *service)
    {
        _getPlayerModelsFromDb = service;
    }
private:
    IPlayerContextJsonBuilder *_jsonBuilder;
    IPlayerContextModelBuilder *_modelBuilder;
    IPlayersDbContext *_dbContext;
    IGetPlayersFromDb * _getPlayerModelsFromDb;
};
#endif // PLAYERSDBSLAS_H
