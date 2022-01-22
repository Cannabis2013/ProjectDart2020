#ifndef ABSTRACTSAVETOSTORAGE_H
#define ABSTRACTSAVETOSTORAGE_H
#include <qstring.h>
class QJsonObject;
template<typename T>
class IDbJsonBuilder;
template<typename T>
class QVector;
template<typename T>
class IModelConverter;
template<typename T>
class IFileDataIO;
template<typename TBaseModel>
class AbstractSaveToStorage
{
public:
    typedef TBaseModel BaseModel;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IFileDataIO<ByteArray> IODevice;
    typedef IDbJsonBuilder<BaseModel> JsonBuilder;
    typedef IModelConverter<BaseModel> Converter;
    struct ServiceProvider
    {
        QVector<BaseModel*> models;
        JsonBuilder *builder;
        Converter *converter;
        IODevice *ioDevice;
    };
    virtual bool save(const QVector<BaseModel*> &models, JsonBuilder *builder, Converter *converter, IODevice *ioDevice)  = 0;
    virtual bool save(const std::initializer_list<ServiceProvider> &list) = 0;
};
#endif // IPERSISTMODELS_H
