#ifndef IDBJSONBUILDER_H
#define IDBJSONBUILDER_H
template<typename T>
class IModelConverter;
class QByteArray;
class QJsonObject;
template<typename T>
class QVector;
template<typename TBaseModel>
class IDbJsonBuilder
{
public:
    typedef TBaseModel BaseModel;
    typedef QVector<BaseModel*> Models;
    typedef QJsonObject Json;
    typedef IModelConverter<BaseModel> Converter;
    virtual QJsonObject toJsonObject(const Json &json, const Models &models, Converter *cvtr) = 0;
};
#endif // IDBJSONBUILDER_H
