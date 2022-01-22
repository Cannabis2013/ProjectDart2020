#ifndef ICONVERTFROMDATA_H
#define ICONVERTFROMDATA_H
class QJsonObject;
class QByteArray;
template<typename T>
class IModelConverter;
template<typename T>
class QVector;
template<typename TBaseModel>
class IConvertFromData
{
public:
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef TBaseModel BaseModel;
    typedef QVector<BaseModel*> Models;
    typedef IModelConverter<BaseModel> Converter;
    virtual Models convert(const ByteArray &json, Converter *cvtr) const = 0;
};
#endif // IDARTSCONVERTFROM_H
