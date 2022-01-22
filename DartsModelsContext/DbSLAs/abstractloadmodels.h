#ifndef ABSTRACTLOADFROMSTORAGE_H
#define ABSTRACTLOADFROMSTORAGE_H
class QJsonObject;
class QByteArray;
template<typename T>
class IModelConverter;
template<typename T>
class IFileDataIO;
template<typename T>class IDbContext;
template<typename T>
class IConvertFromData;
template<typename T>
class QVector;
template<typename TModel>
class AbstractLoadModels
{
public:
    typedef TModel BaseModel;
    typedef QVector<BaseModel*> Models;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IConvertFromData<BaseModel> ModelBuilder;
    typedef IModelConverter<BaseModel> Converter;
    typedef IDbContext<TModel> DbContext;
    typedef IFileDataIO<ByteArray> IODevice;
    virtual void load(DbContext *dbContext,ModelBuilder *builder, Converter *converter, IODevice *ioDevice) const = 0;
};
#endif // IFETCHMEMDB_H
