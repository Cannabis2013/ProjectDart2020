#ifndef IFETCHDB_H
#define IFETCHDB_H
template<typename T>
class IFileDataIO;
template<typename T,typename U>
class ICreateModelsFrom;
template<typename TDbCtx, typename TIODevice, typename TModelBuilder>
class IFetchDb
{
public:
    typedef TDbCtx DbCtx;
    typedef TIODevice IODevice;
    typedef TModelBuilder ModelBuilder;
    virtual bool fetch(DbCtx *dbCtx, ModelBuilder *builder, IODevice *ioDevice) const = 0;
};
#endif // ILOADMODELS_H
