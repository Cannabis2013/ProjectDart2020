#ifndef IDCMODELSCONVERTER_H
#define IDCMODELSCONVERTER_H
class QJsonObject;
class QByteArray;
template<typename T>
class IDCModelConverter;
template<typename T>
class QVector;
template<typename TModel>
class IDCModelsConverter
{
public:
    typedef TModel Model;
    typedef QVector<Model> Models;
    typedef IDCModelConverter<Model> ModelBuilder;
    virtual Models convert(const QByteArray &byteArray, ModelBuilder *builder) const = 0;
};
#endif // IDCCONVERTTOMODELS_H
