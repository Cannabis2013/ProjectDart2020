#ifndef IMODELCONVERTER_H
#define IMODELCONVERTER_H
class QJsonObject;
class QByteArray;
class IDartsInputBuilder;
template<typename T>
class QVector;
template<typename TModel>
class IModelConverter
{
public:
    typedef TModel Model;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    virtual Json create(Model* model) const = 0;
    virtual Model *create(const ByteArray &byteArray) const = 0;
    virtual Model* create(const Json &d) const = 0;
};
#endif // IJSONBUILDER_H
