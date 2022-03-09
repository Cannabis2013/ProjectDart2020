#ifndef SAVEPLAYERMODELS_H
#define SAVEPLAYERMODELS_H
#include "isaveplayers.h"
class IPlayer;
class QByteArray;
class IFileDataIO;
template<typename T>
class IPlayersDbContext;
template<typename T>
class IJsonBuilder;
namespace SvPlaCtx{
    typedef IPlayer Model;
    typedef QByteArray Json;
    typedef IPlayersDbContext<Model> DbCtx;
    typedef IFileDataIO FileDataIO;
    typedef IJsonBuilder<Model> DataAdder;
}
class SavePlayerModels : public ISavePlayers<SvPlaCtx::FileDataIO,
        SvPlaCtx::DbCtx,SvPlaCtx::DataAdder>
{
public:
    virtual bool save(DbCtx *dbCtx, IODevice *ioDevice, DataManCtx *dataAdder) override;
};
#endif // SAVEPLAYERMODELS_H
