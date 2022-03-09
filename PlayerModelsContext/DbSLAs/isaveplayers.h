#ifndef ISAVEPLAYERS_H
#define ISAVEPLAYERS_H

template<typename TIODevice, typename TDbContext, typename TDataCtx>
class ISavePlayers
{
public:
    typedef TDbContext DbCtx;
    typedef TIODevice IODevice;
    typedef TDataCtx DataManCtx;
    virtual bool save(DbCtx *dbCtx, IODevice *ioDevice, DataManCtx *dataManCtx) = 0;
};
#endif // ISAVEPLAYERS_H
