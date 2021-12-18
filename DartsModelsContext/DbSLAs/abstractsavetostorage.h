#ifndef ABSTRACTSAVETOSTORAGE_H
#define ABSTRACTSAVETOSTORAGE_H
#include <functional>
template<typename T,typename  U>
class IModelConverter;
template<typename T>
class IFileDataIO;
template<typename TModel, typename TData, typename TDbContext, typename TConverter>
class AbstractSaveToStorage
{
public:
    typedef TModel Model;
    typedef TData Data;
    typedef IFileDataIO<Data> IODevice;
    typedef TDbContext DbCtx;
    typedef TConverter Converter;
    struct ServiceProvider
    {
        DbCtx *dbContext;
        Converter *converter;
    };
    AbstractSaveToStorage(IODevice *ioDevice) {setIoDevice(ioDevice);}
    virtual bool save(DbCtx *dbCtx, Converter *converter)  = 0;
    virtual bool save(const std::initializer_list<ServiceProvider> &list) = 0;
    IODevice *ioDevice() const{return _ioDevice;};
    void setIoDevice(IODevice *newIoDevice) {_ioDevice = newIoDevice;}
private:
    IFileDataIO<Data> *_ioDevice;
};
#endif // IPERSISTMODELS_H
