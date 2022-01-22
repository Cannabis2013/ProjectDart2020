#ifndef IDCMODELSCONVERTER_H
#define IDCMODELSCONVERTER_H
class QByteArray;
template<typename T, typename U>
class IDCModelBuilder;
template<typename T>
class QVector;
template<typename TModel, typename TJson>
class IDCModelsConverter
{
public:
    typedef TModel Model;
    typedef TJson Json;
    typedef QVector<Model> Models;
    typedef IDCModelBuilder<Model,Json> ModelBuilder;
    virtual Models convert(const QByteArray &byteArray, ModelBuilder *builder) const = 0;
};
#endif // IDCCONVERTTOMODELS_H
