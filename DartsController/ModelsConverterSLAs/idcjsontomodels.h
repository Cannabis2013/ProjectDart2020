#ifndef IDCJSONTOMODELS_H
#define IDCJSONTOMODELS_H
class QJsonObject;
class QByteArray;
template<typename T> class IDCJsonToModel;
template<typename T> class QVector;
template<typename TModel>
class IDCJsonToModels
{
public:
    typedef TModel Model;
    typedef QVector<Model> Models;
    typedef IDCJsonToModel<Model> ModelBuilder;
    virtual Models convert(const QByteArray &byteArray, ModelBuilder *builder) const = 0;
};
#endif // IDCCONVERTTOMODELS_H
