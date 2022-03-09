#ifndef LOADPLAYERMODELS_H
#define LOADPLAYERMODELS_H
#include "DbSLAs/ifetchdb.h"
class QByteArray;
template<typename T>
class IPlayersDbContext;
class IFileDataIO;
class IPlayer;
template<typename T, typename U>
class IPlayerBuilder;
template<typename T>
class QVector;
namespace LdPlaMds
{
    typedef IPlayersDbContext<IPlayer> DbCtx;
    typedef IFileDataIO IODevice;
    typedef IPlayerBuilder<IPlayer,QByteArray> MdBuilder;
}
class LoadPlayerModels : public IFetchDb<LdPlaMds::DbCtx,LdPlaMds::IODevice,LdPlaMds::MdBuilder>
{
public:
    typedef IPlayer Model;
    virtual bool fetch(DbCtx *dbCtx, ModelBuilder *builder, IODevice *ioDevice) const override;
private:
    void fetchDb(const QVector<Model*> &models, DbCtx *dbCtx) const;
};

#endif // LOADPLAYERMODELS_H
