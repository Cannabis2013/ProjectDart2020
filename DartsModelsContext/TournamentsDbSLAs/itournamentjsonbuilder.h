#ifndef ITOURNAMENTJSONBUILDER_H
#define ITOURNAMENTJSONBUILDER_H
class QByteArray;
class QJsonObject;
template<typename T>
class QVector;
template<typename T>
class IModelConverter;
class QUuid;
template<typename T>
class IModel;
template<typename TModel>
class IDartsJsonBuilder
{
public:
    typedef TModel Model;
    typedef QJsonObject JsonObject;
    typedef QByteArray ByteArray;
    typedef IModelConverter<Model> ModelConverter;
    virtual ByteArray create(Model *model, ModelConverter *cvt) const = 0;
    virtual ByteArray create(const QVector<Model*>& models, ModelConverter *cvt) const = 0;
};
#endif // ICREATEJSONFROMDARTSINPUT_H
