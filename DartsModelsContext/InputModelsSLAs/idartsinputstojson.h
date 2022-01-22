#ifndef IDARTSINPUTSTOJSON_H
#define IDARTSINPUTSTOJSON_H
class QJsonObject;
class QByteArray;
template<typename T>
class QVector;
template<typename T>
class IModelConverter;
template<typename TBaseModel>
class IDartsInputsToJson
{
public:
    typedef TBaseModel BaseModel;
    typedef QVector<BaseModel*> Models;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IModelConverter<BaseModel> Converter;
    virtual ByteArray toJson(const Models &models, Converter *cvtr) const = 0;
};
#endif // IINPUTSTOJSON_H
